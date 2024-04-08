/*############################################################################
  # Copyright (C) Intel Corporation
  #
  # SPDX-License-Identifier: MIT
  ############################################################################*/

#ifndef LIBVPL_SRC_MFX_DISPATCHER_VPL_WIN_H_
#define LIBVPL_SRC_MFX_DISPATCHER_VPL_WIN_H_

// headers for Windows legacy dispatcher
#if defined(_WIN32) || defined(_WIN64)
    #include "windows/mfx_dispatcher.h"
    #include "windows/mfx_dispatcher_defs.h"
    #include "windows/mfx_dxva2_device.h"
    #include "windows/mfx_library_iterator.h"
    #include "windows/mfx_load_dll.h"
#endif

#endif // LIBVPL_SRC_MFX_DISPATCHER_VPL_WIN_H_
