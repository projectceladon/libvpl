/*############################################################################
  # Copyright (C) 2005 Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

#ifndef __SAMPLE_VPP_CONFIG_H
    #define __SAMPLE_VPP_CONFIG_H

    #include <vector>

    #include "vpl/mfxvideo++.h"
    #include "vpl/mfxvideo.h"

    #ifndef MFX_VERSION
        #error MFX_VERSION not defined
    #endif

enum { NOT_INIT_VALUE = 0xFFF7 };

enum MemType { SYSTEM_MEMORY = 0x00, D3D9_MEMORY = 0x01, D3D11_MEMORY = 0x02, VAAPI_MEMORY = 0x03 };

    #define VPP_PROCAMP_BRIGHTNESS_DEFAULT 0.0
    #define VPP_PROCAMP_CONTRAST_DEFAULT   1.0
    #define VPP_PROCAMP_HUE_DEFAULT        0.0
    #define VPP_PROCAMP_SATURATION_DEFAULT 1.0

    #define VPP_DENOISE_FACTOR_DEFAULT NOT_INIT_VALUE
    #define VPP_FILTER_FACTOR_DEFAULT  NOT_INIT_VALUE

    #define MULTI_VIEW_COUNT_MAX (1024)
    #define MAX_INPUT_STREAMS    64

typedef enum {
    VPP_FILTER_DISABLED           = 0,
    VPP_FILTER_ENABLED_DEFAULT    = 1,
    VPP_FILTER_ENABLED_CONFIGURED = 7

} FilterConfig;

typedef struct {
    FilterConfig mode;

} sVideoAnalysisParam;

typedef struct {
    FilterConfig mode;

} sVarianceReportParam;

typedef struct {
    FilterConfig mode;

} sIDetectParam; // for interlace detection algorithm (PICSTRUCT_DETECTION)
typedef struct {
    mfxF64 brightness;
    mfxF64 contrast;
    mfxF64 saturation;
    mfxF64 hue;

    FilterConfig mode;

} sProcAmpParam;

struct sVideoSignalInfoParam : public mfxExtVPPVideoSignalInfo {
    FilterConfig mode;
    sVideoSignalInfoParam() : mode(VPP_FILTER_DISABLED) {
        In.NominalRange   = MFX_NOMINALRANGE_UNKNOWN;
        In.TransferMatrix = MFX_TRANSFERMATRIX_UNKNOWN;
        Out               = In;
    };
};

struct sMirroringParam : public mfxExtVPPMirroring {
    FilterConfig mode;
    sMirroringParam() : mode(VPP_FILTER_DISABLED) {
        Type = MFX_MIRRORING_DISABLED;
    };
};

typedef struct {
    mfxU16 factor;
    FilterConfig mode;
    mfxU16 config;
} sDenoiseParam;

struct sColorFillParam : public mfxExtVPPColorFill {
    FilterConfig mode;
    sColorFillParam() : mfxExtVPPColorFill(), mode(VPP_FILTER_DISABLED) {}
};

    #ifdef ENABLE_MCTF
typedef struct {
    mfxExtVppMctf params;
    FilterConfig mode;
} sMCTFParam;
    #endif

typedef struct {
    mfxU16 factor;
    FilterConfig mode;

} sDetailParam;

typedef struct {
    mfxU32 algorithm;
    FilterConfig mode;

} sFrameRateConversionParam;

typedef struct {
    mfxU16 algorithm;
    mfxU16 tc_pattern;
    mfxU16 tc_pos;
    FilterConfig mode;

} sDIParam;

typedef struct {
    char streamName[MSDK_MAX_FILENAME_LEN];
    mfxVPPCompInputStream compStream;
    mfxU32 streamFourcc;
} sCompositionStreamInfo;

typedef struct {
    sCompositionStreamInfo streamInfo[MAX_INPUT_STREAMS];

    FilterConfig mode;
} sCompositionParam;

//------------------------------------------
// MSDK 3.0 (re-priority)
//------------------------------------------
typedef struct {
    bool bBT709;

    FilterConfig mode;

} sGamutMappingParam;

//------------------------------------------
// MSDK API 1.5
//------------------------------------------

typedef struct {
    mfxU16 Red;
    mfxU16 Green;
    mfxU16 Blue;
    mfxU16 Cyan;
    mfxU16 Magenta;
    mfxU16 Yellow;

    FilterConfig mode;

} sTccParam;

typedef struct {
    FilterConfig mode;

} sAceParam;

typedef struct {
    mfxU16 SkinToneFactor;

    FilterConfig mode;

} sSteParam;

typedef struct {
    mfxU8 istabMode;

    FilterConfig mode;

} sIStabParam;

//-------------------------------------------------------

typedef struct {
    mfxU16 viewCount;
    FilterConfig mode;

} sMultiViewParam;

typedef struct {
    mfxU16 active;
    mfxU16 width;
    mfxU16 height;

    // cropX/Y/W/H will be added ASAP
    mfxU16 cropX;
    mfxU16 cropY;
    mfxU16 cropW;
    mfxU16 cropH;

} sSVCLayerDescr;

typedef struct {
    sSVCLayerDescr descr[8];
    FilterConfig mode;

} sSVCParam;

class ViewGenerator {
public:
    ViewGenerator(mfxU16 viewCount) : m_viewID(viewCount - 1), m_viewCount(viewCount) {}
    ~ViewGenerator(void) {
        m_viewID    = 0;
        m_viewCount = 0;
    }

    mfxU16 GetNextViewID(void) {
        m_viewID++;
        m_viewID %= m_viewCount;
        return m_viewID;
    };
    mfxU16 GetViewIndx(mfxU16 viewID) {
        return viewID;
    };

private:
    mfxU16 m_viewID;
    mfxU16 m_viewCount;
};

typedef struct {
    FilterConfig mode;
    mfxU16 VideoFullRange;
    mfxU16 ColourPrimaries;
    mfxU16 TransferCharacteristics;
} sVideoSignalInfo;

#endif /* __SAMPLE_VPP_CONFIG_H */
/* EOF */
