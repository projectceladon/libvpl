/*############################################################################
  # Copyright (C) 2005 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

#include "mfx_samples_config.h"

#include "general_allocator.h"

#if defined(_WIN32) || defined(_WIN64)
    #include "d3d11_allocator.h"
    #include "d3d_allocator.h"

#else
    #include <stdarg.h>
    #include "vaapi_allocator.h"
#endif

#include "sysmem_allocator.h"

#include "sample_defs.h"

// Wrapper on standard allocator for concurrent allocation of
// D3D and system surfaces
GeneralAllocator::GeneralAllocator()
        : m_MidsGuard(),
          m_Mids(),
          m_D3DAllocator(),
          m_SYSAllocator(){};
GeneralAllocator::~GeneralAllocator(){};
mfxStatus GeneralAllocator::Init(mfxAllocatorParams* pParams) {
    mfxStatus sts = MFX_ERR_NONE;

#if defined(_WIN32) || defined(_WIN64)
    D3DAllocatorParams* d3dAllocParams = dynamic_cast<D3DAllocatorParams*>(pParams);
    if (d3dAllocParams)
        m_D3DAllocator.reset(new D3DFrameAllocator);
    #if MFX_D3D11_SUPPORT
    D3D11AllocatorParams* d3d11AllocParams = dynamic_cast<D3D11AllocatorParams*>(pParams);
    if (d3d11AllocParams)
        m_D3DAllocator.reset(new D3D11FrameAllocator);
    #endif
#endif

#ifdef LIBVA_SUPPORT
    vaapiAllocatorParams* vaapiAllocParams = dynamic_cast<vaapiAllocatorParams*>(pParams);
    if (vaapiAllocParams)
        m_D3DAllocator.reset(new vaapiFrameAllocator);
#endif

    if (m_D3DAllocator.get()) {
        sts = m_D3DAllocator.get()->Init(pParams);
        MSDK_CHECK_STATUS(sts, "m_D3DAllocator.get failed");
    }

    m_SYSAllocator.reset(new SysMemFrameAllocator());
    sts = m_SYSAllocator->Init(0);
    MSDK_CHECK_STATUS(sts, "m_SYSAllocator.get failed");

    return sts;
}
mfxStatus GeneralAllocator::Close() {
    mfxStatus sts = MFX_ERR_NONE;
    if (m_D3DAllocator.get()) {
        sts = m_D3DAllocator.get()->Close();
        MSDK_CHECK_STATUS(sts, "m_D3DAllocator.get failed");
    }

    sts = m_SYSAllocator.get()->Close();
    MSDK_CHECK_STATUS(sts, "m_SYSAllocator.get failed");

    return sts;
}

mfxStatus GeneralAllocator::LockFrame(mfxMemId mid, mfxFrameData* ptr) {
    if (isD3DMid(mid) && m_D3DAllocator.get())
        return m_D3DAllocator.get()->Lock(m_D3DAllocator.get(), mid, ptr);
    else
        return m_SYSAllocator.get()->Lock(m_SYSAllocator.get(), mid, ptr);
}
mfxStatus GeneralAllocator::UnlockFrame(mfxMemId mid, mfxFrameData* ptr) {
    if (isD3DMid(mid) && m_D3DAllocator.get())
        return m_D3DAllocator.get()->Unlock(m_D3DAllocator.get(), mid, ptr);
    else
        return m_SYSAllocator.get()->Unlock(m_SYSAllocator.get(), mid, ptr);
}

mfxStatus GeneralAllocator::GetFrameHDL(mfxMemId mid, mfxHDL* handle) {
    if (isD3DMid(mid) && m_D3DAllocator.get())
        return m_D3DAllocator.get()->GetHDL(m_D3DAllocator.get(), mid, handle);
    else
        return m_SYSAllocator.get()->GetHDL(m_SYSAllocator.get(), mid, handle);
}

mfxStatus GeneralAllocator::ReleaseResponse(mfxFrameAllocResponse* response) {
    // try to ReleaseResponse via D3D allocator
    if (isD3DMid(response->mids[0]) && m_D3DAllocator.get())
        return m_D3DAllocator.get()->Free(m_D3DAllocator.get(), response);
    else
        return m_SYSAllocator.get()->Free(m_SYSAllocator.get(), response);
}

mfxStatus GeneralAllocator::ReallocImpl(mfxMemId mid,
                                        const mfxFrameInfo* info,
                                        mfxU16 memType,
                                        mfxMemId* midOut) {
    if (!info || !midOut)
        return MFX_ERR_NULL_PTR;

    mfxStatus sts;
    if ((memType & MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ||
         memType & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) &&
        m_D3DAllocator.get()) {
        sts = m_D3DAllocator.get()->ReallocFrame(mid, info, memType, midOut);
        MSDK_CHECK_NOT_EQUAL(MFX_ERR_NONE, sts, sts);
    }
    else {
        sts = m_SYSAllocator.get()->ReallocFrame(mid, info, memType, midOut);
        MSDK_CHECK_NOT_EQUAL(MFX_ERR_NONE, sts, sts);
    }
    return sts;
}

mfxStatus GeneralAllocator::AllocImpl(mfxFrameAllocRequest* request,
                                      mfxFrameAllocResponse* response) {
    mfxStatus sts;
    if ((request->Type & MFX_MEMTYPE_VIDEO_MEMORY_DECODER_TARGET ||
         request->Type & MFX_MEMTYPE_VIDEO_MEMORY_PROCESSOR_TARGET) &&
        m_D3DAllocator.get()) {
        sts = m_D3DAllocator.get()->Alloc(m_D3DAllocator.get(), request, response);
        MSDK_CHECK_NOT_EQUAL(MFX_ERR_NONE, sts, sts);
        StoreFrameMids(true, response);
    }
    else {
        sts = m_SYSAllocator.get()->Alloc(m_SYSAllocator.get(), request, response);
        MSDK_CHECK_NOT_EQUAL(MFX_ERR_NONE, sts, sts);
        StoreFrameMids(false, response);
    }
    return sts;
}
void GeneralAllocator::StoreFrameMids(bool isD3DFrames, mfxFrameAllocResponse* response) {
    std::lock_guard<std::mutex> midsGuard(m_MidsGuard);
    for (mfxU32 i = 0; i < response->NumFrameActual; i++)
        m_Mids.insert(std::pair<mfxHDL, bool>(response->mids[i], isD3DFrames));
}
bool GeneralAllocator::isD3DMid(mfxHDL mid) {
    std::lock_guard<std::mutex> midsGuard(m_MidsGuard);
    std::map<mfxHDL, bool>::iterator it;
    it = m_Mids.find(mid);
    if (it == m_Mids.end())
        return false; // sys mem allocator will check validity of mid further
    else
        return it->second;
}

mfxStatus GeneralAllocator::Create3DLutMemory(mfxMemId memId, const char* lut3d_file_name) {
    mfxStatus sts = MFX_ERR_NONE;
#ifdef LIBVA_SUPPORT
    vaapiFrameAllocator* pAllocator = dynamic_cast<vaapiFrameAllocator*>(m_D3DAllocator.get());
    if (pAllocator) {
        sts = pAllocator->Create3DLutMemory(memId, lut3d_file_name);
    }
    else {
        sts = MFX_ERR_NULL_PTR;
    }
#endif
    return sts;
}
mfxStatus GeneralAllocator::Release3DLutMemory(mfxMemId memId) {
    mfxStatus sts = MFX_ERR_NONE;
#ifdef LIBVA_SUPPORT
    vaapiFrameAllocator* pAllocator = dynamic_cast<vaapiFrameAllocator*>(m_D3DAllocator.get());
    if (pAllocator) {
        sts = pAllocator->Release3DLutMemory(memId);
    }
    else {
        sts = MFX_ERR_NULL_PTR;
    }
#endif
    return sts;
}
