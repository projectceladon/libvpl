#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
#include "vpl/mfx.h"
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 2) {
#ifdef _WIN32
        printf("usage: hello-multiadapter AdapterNum\n");
#else
        printf("usage: hello-multiadapter DRMRenderNodeNum\n");
#endif
        return -1;
    }

#ifdef ONEVPL_EXPERIMENTAL
	printf("Build ONEVPL_EXPERIMENTAL APIs.\n");
#endif

    mfxSession session = NULL;
    mfxConfig cfg[2];
    mfxVariant cfgVal[2];
    mfxLoader loader = MFXLoad();
	
    cfg[0] = MFXCreateConfig(loader);
    cfgVal[0].Type = MFX_VARIANT_TYPE_U32;
    cfgVal[0].Data.U32 = MFX_IMPL_TYPE_HARDWARE;
    mfxStatus sts =
        MFXSetConfigFilterProperty(cfg[0], (const mfxU8*)"mfxImplDescription.Impl", cfgVal[0]);
    if (MFX_ERR_NONE != sts)
        printf("MFXSetConfigFilterProperty 0 error=%d\n", sts);
	
    mfxU8* filter;
#ifdef _WIN32
    filter = (mfxU8*)"DXGIAdapterIndex";
	//or
	//filter = (mfxU8*)"mfxImplDescription.VendorImplID";
	printf("Filter hardware query by: %s\n", filter);
#else
    //filter = (mfxU8*)"mfxImplDescription.DRMRenderNodeNum";
    filter = (mfxU8*)"mfxExtendedDeviceId.DRMRenderNodeNum";
#endif
    cfg[1] = MFXCreateConfig(loader);
    cfgVal[1].Type = MFX_VARIANT_TYPE_U32;
    cfgVal[1].Data.U32 = atoi(argv[1]);
    sts = MFXSetConfigFilterProperty(cfg[1], filter, cfgVal[1]);
    if (MFX_ERR_NONE != sts)
        printf("MFXSetConfigFilterProperty 1 error=%d\n", sts);

    sts = MFXCreateSession(loader, 0, &session);
    if (MFX_ERR_NONE != sts) {
        printf("MFXCreateSession error=%d\n", sts);
        if (MFX_ERR_NOT_FOUND == sts) {
            printf("No implementations could be found meeting criteria specified\n");
        }
    }
    else {
        mfxImplDescription* iDesc = nullptr;

        // Loads info about implementation at specified list location
        sts = MFXEnumImplementations(loader, 0, MFX_IMPLCAPS_IMPLDESCSTRUCTURE, (mfxHDL*)&iDesc);
        if (MFX_ERR_NONE != sts)
            printf("MFXEnumImplementations error=%d\n", sts);

        printf("Implementation used to create session:\n");
        printf("  ApiVersion:           %hu.%hu  \n",
            iDesc->ApiVersion.Major,
            iDesc->ApiVersion.Minor);
        printf("  Implementation type:  %s\n",
            (iDesc->Impl == MFX_IMPL_TYPE_SOFTWARE) ? "SW" : "HW");
        printf("%2sApiVersion.Major: 0x%04X\n", "", iDesc->ApiVersion.Major);
		printf("%2sApiVersion.Minor: 0x%04X\n", "", iDesc->ApiVersion.Minor);
		printf("%2sImplementation Name: %s\n", "", iDesc->ImplName);
		printf("%2sLicense: %s\n", "", iDesc->License);
		printf("%2sKeywords: %s\n", "", iDesc->Keywords);
		printf("%2sVendorID: 0x%04X\n", "", iDesc->VendorID);
		printf("%2sVendorImplID: 0x%04X\n", "", iDesc->VendorImplID);
		
        MFXDispReleaseImplDescription(loader, iDesc);

        mfxHDL implPath = nullptr;
        sts = MFXEnumImplementations(loader, 0, MFX_IMPLCAPS_IMPLPATH, &implPath);
        if (MFX_ERR_NONE != sts)
            printf("MFXEnumImplementations error=%d\n", sts);

        printf("  Path: %s\n\n", reinterpret_cast<mfxChar*>(implPath));
        MFXDispReleaseImplDescription(loader, implPath);

#ifdef ONEVPL_EXPERIMENTAL
		printf("Enable mfxExtendedDeviceId with ONEVPL_EXPERIMENTAL APIs.\n");
        mfxExtendedDeviceId* idescDevice;

        sts = MFXEnumImplementations(loader,
            0,
            MFX_IMPLCAPS_DEVICE_ID_EXTENDED,
            reinterpret_cast<mfxHDL*>(&idescDevice));
        if (MFX_ERR_NONE != sts) {
            printf("MFXEnumImplementations MFX_IMPLCAPS_DEVICE_ID_EXTENDED error=%d\n", sts);
        }
        else {
            printf("%6sDeviceName: %s\n", "", idescDevice->DeviceName);
            printf("%6sExtended DeviceID's:\n", "");
            printf("%6sVendorID: 0x%04X\n", "", idescDevice->VendorID);
		    printf("%6sDeviceID: 0x%04X\n", "", idescDevice->DeviceID);
            printf("%6sPCIDomain: 0x%08X\n", "", idescDevice->PCIDomain);
            printf("%6sPCIBus: 0x%08X\n", "", idescDevice->PCIBus);
            printf("%6sPCIdevice: 0x%08X\n", "", idescDevice->PCIDevice);
            printf("%6sPCIFunction: 0x%08X\n", "", idescDevice->PCIFunction);
            printf("%6sDRMRenderNodeNum: %d\n", "", idescDevice->DRMRenderNodeNum);
            printf("%6sDRMPrimaryNodeNum: 0x%04X\n", "", idescDevice->DRMPrimaryNodeNum);
            printf("%6sLUIDValid: 0x%04X\n", "", idescDevice->LUIDValid);

			if (idescDevice->LUIDValid) {
                printf("%6sDeviceLUID: ", "");
                for (mfxU32 idx = 0; idx < 8; idx++) {
                    printf("%02x", idescDevice->DeviceLUID[7 - idx]);
                }
                printf("\n");
                printf("%6sLUIDDeviceNodeMask: 0x%04X\n", "", idescDevice->LUIDDeviceNodeMask);
            }
			
#ifndef _WIN32
            printf("  DRMRenderNodeNum: %d\n", idescDevice->DRMRenderNodeNum);
#endif
        }

        MFXDispReleaseImplDescription(loader, idescDevice);
#endif

        MFXClose(session);
    }

    if (loader)
        MFXUnload(loader);

    return 0;
}
