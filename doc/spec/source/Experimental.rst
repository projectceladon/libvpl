.. SPDX-FileCopyrightText: 2021 Intel Corporation
..
.. SPDX-License-Identifier: CC-BY-4.0

=================================
|vpl_short_name| Experimental API
=================================

All API entries defined under the ONEVPL_EXPERIMENTAL macro are considered as
experimental. Backward compatibility is not guaranteed for these features.
Future presence is not guaranteed as well.

By default, experimental API is turned off in the header files. To enable
it, need to define ONEVPL_EXPERIMENTAL macro during the application
compilation stage.

The following is a list of experimental interfaces, starting from API version
2.6.

.. _experimental-api-table:

.. list-table:: Experimental API
   :header-rows: 1
   :widths: auto

   * - **Experimental API**
     - **Added in API Version**
     - **Removed in API Version**
     - **Removal Reason**
   * - :cpp:struct:`mfxExtendedDeviceId`
     - 2.6
     - 2.10 
     - Moved to production
   * - ``mfxExtCodingOption3::CPUEncToolsProcessing``
     - 2.6
     - 2.10
     - Redundant parameter
   * - :cpp:type:`mfxExtRefListCtrl`
     - 2.6
     - 2.8
     - Moved to production
   * - :cpp:enumerator:`MFX_EXTBUFF_UNIVERSAL_REFLIST_CTRL`
     - 2.6
     - 2.8
     - Moved to production
   * - Extended enum for :cpp:member:`mfxExtDecodeErrorReport::ErrorTypes`
     - 2.6
     - 2.7
     - Moved to production
   * - :cpp:enumerator:`mfxHandleType::MFX_HANDLE_PXP_CONTEXT`
     - 2.6
     - 2.7
     - Moved to production
   * - :cpp:struct:`mfxRefInterface`
     - 2.7
     - 2.10 
     - Moved to production
   * - All definitions in mfxencodestats.h
     - 2.7
     -
     -
   * - :cpp:enumerator:`MFX_FOURCC_ABGR16F` FourCC definition
     - 2.8
     - 2.10
     - Moved to production
   * - :cpp:enumerator:`MFX_CONTENT_NOISY_VIDEO` ContentInfo definition
     - 2.8
     - 2.10 
     - Moved to production
   * - Camera Processing API for RAW acceleration
     - 2.8
     - 2.10
     - Moved to production
   * - Hint to disable external video frames caching for GPU copy
     - 2.8
     - 2.10 
     - Moved to production
   * - :cpp:member:`mfxExtMBQP::Pitch`
     - 2.8
     - 2.10
     - Moved to production
   * - :cpp:struct:`mfxExtSyncSubmission`
     - 2.9
     -
     -
   * - :cpp:struct:`mfxExtVPPPercEncPrefilter`
     - 2.9
     -
     -
   * - :cpp:member:`mfxExtendedDeviceId::RevisionID`
     - 2.9
     - 2.10 
     - Moved to production
   * - :cpp:struct:`extDeviceUUID`
     - 2.9
     - 2.10 
     - Moved to production
   * - :cpp:struct:`mfxExtTuneEncodeQuality`
     - 2.9
     -
     -
   * - ``MFX_ENCODE_TUNE_DEFAULT``
     - 2.9
     - 2.10
     - Changed to :cpp:enumerator:`MFX_ENCODE_TUNE_OFF`
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_PSNR`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_SSIM`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_MS_SSIM`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_VMAF`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_PERCEPTUAL`
     - 2.9
     -
     -
   * - :cpp:enumerator:`MFX_EXTBUFF_TUNE_ENCODE_QUALITY`
     - 2.9
     -
     -
   * - :cpp:struct:`mfxAutoSelectImplDeviceHandle`
     - 2.9
     - 
     - 
   * - :cpp:type:`mfxAutoSelectImplType`
     - 2.9
     - 
     - 
   * - :cpp:enumerator:`mfxAutoSelectImplType::MFX_AUTO_SELECT_IMPL_TYPE_UNKNOWN`
     - 2.9
     -  
     - 
   * - :cpp:enumerator:`mfxAutoSelectImplType::MFX_AUTO_SELECT_IMPL_TYPE_DEVICE_HANDLE`
     - 2.9
     - 
     - 
   * - :cpp:enumerator:`MFX_CORRUPTION_HW_RESET`
     - 2.10
     -
     -
   * - :cpp:enumerator:`MFX_ENCODE_TUNE_OFF`
     - 2.10
     -
     -
   * - :cpp:struct:`mfxMemoryInterface`
     - 2.10
     -
     -
   * - :cpp:enumerator:`mfxHandleType::MFX_HANDLE_MEMORY_INTERFACE`
     - 2.10
     -
     -
   * - :cpp:enum:`mfxSurfaceComponent`
     - 2.10
     -
     -
   * - :cpp:enum:`mfxSurfaceType`
     - 2.10
     -
     -
   * - :cpp:struct:`mfxSurfaceHeader`
     - 2.10
     -
     -
   * - :cpp:struct:`mfxSurfaceInterface`
     - 2.10
     -
     -
   * - :cpp:struct:`mfxSurfaceD3D11Tex2D`
     - 2.10
     -
     -
   * - :cpp:struct:`mfxSurfaceVAAPI`
     - 2.10
     -
     -
   * - :cpp:struct:`mfxSurfaceOpenCLImg2D`
     - 2.10
     -
     -
   * - :cpp:struct:`mfxExtSurfaceOpenCLImg2DExportDescription`
     - 2.10
     -
     -
   * - :cpp:enum:`mfxImplCapsDeliveryFormat`
     - 2.10
     -
     -
   * - :cpp:struct:`mfxSurfaceTypesSupported`
     - 2.10
     -
     -
   * - :cpp:struct:`mfxConfigInterface`
     - 2.10
     -
     -
   * - :cpp:enumerator:`mfxHandleType::MFX_HANDLE_CONFIG_INTERFACE`
     - 2.10
     -
     -
   * - :cpp:enum:`mfxStructureType`
     - 2.10
     -
     -
   * - :cpp:enumerator:`mfxStatus::MFX_ERR_MORE_EXTBUFFER`
     - 2.10
     -
     -

