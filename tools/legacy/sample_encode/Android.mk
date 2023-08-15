# Copyright(c) 2023 Intel Corporation

# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files(the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and / or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
# OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.

LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(addprefix src/, $(notdir $(wildcard $(LOCAL_PATH)/src/*.cpp)))

LOCAL_SHARED_LIBRARIES := \
    libvpl \
	libva \
	libva-android

LOCAL_STATIC_LIBRARIES := \
    vpl_libsample_common

LOCAL_CPPFLAGS := \
    -std=c++14 \
	-frtti \
	-Wall \
	-fexceptions \
	-Wno-unused-variable \
	-Wunused-parameter \
	-Wmissing-field-initializers \
	-DMFX_DEPRECATED_OFF \
	-DLIBVA_SUPPORT \
	-DLIBVA_ANDROID_SUPPORT

LOCAL_CFLAGS := $(LOCAL_CPPFLAGS)

LOCAL_C_INCLUDES  := \
    $(LOCAL_PATH)/include \
	vendor/intel/external/onevpl/api \
	vendor/intel/external/onevpl/tools/legacy/media_sdk_compatibility_headers \
	vendor/intel/external/onevpl/tools/legacy/sample_common/include \
	hardware/intel/external/libva

LOCAL_MODULE := vpl_sample_encoder
LOCAL_PROPRIETARY_MODULE := true

include $(BUILD_EXECUTABLE)