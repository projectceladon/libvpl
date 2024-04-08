# `legacy-encode` Sample

This sample shows how to use the Intel� Video Processing Library (Intel� VPL) 1.35 common API to
perform a simple video encode.

| Optimized for    | Description
|----------------- | ----------------------------------------
| OS               | Ubuntu* 20.04/22.04; Windows* 10
| Hardware         | Compatible with Intel� VPL GPU implementation, which can be found at https://github.com/intel/libvpl-intel-gpu 
|                  | and Intel� Media SDK GPU implementation, which can be found at https://github.com/Intel-Media-SDK/MediaSDK
| What You Will Learn | How to use Intel� VPL to encode an raw video file to H.265
| Time to Complete | 5 minutes


## Purpose

This sample is a command line application that takes a file containing a raw
native format video elementary stream as an argument, encodes it with Intel� VPL and
writes the encoded output to `out.h265` in H.265 format.

Native raw frame format: GPU=NV12.

## Key Implementation details

| Configuration     | Default setting
| ----------------- | ----------------------------------
| Target device     | GPU
| Input format      | NV12
| Output format     | H.265 video elementary stream
| Output resolution | same as input


## License

This code sample is licensed under MIT license.


## Building the `legacy-encode` Program

### On a Linux* System

Perform the following steps:

1. Install prerequisites. To build and run the sample you need to install prerequisite software and set up your environment:

   - Follow the steps in [install.md](https://github.com/intel/libvpl/blob/master/INSTALL.md) or install libvpl-dev.
   - Follow the steps in [dgpu-docs](https://dgpu-docs.intel.com/) according to your GPU.
   - Install the packages using following commands:
   ```
   apt update
   apt install -y cmake build-essential pkg-config libva-dev libva-drm2 vainfo
   ```

2. Set up your environment using the following command.
   ```
   source <vpl_install_dir>/etc/vpl/vars.sh
   ```
   Here `<vpl_install_dir>` represents the root folder of your Intel� VPL installation. If you customized the
   installation folder, it is in your custom location.

3. Build the program using the following commands:
   ```
   mkdir build
   cd build
   cmake -DCMAKE_BUILD_TYPE=Release ..
   cmake --build .
   ```

4. Run the program using the following command:
   ```
   ./legacy-encode -i ../../../content/cars_320x240.i420 -w 320 -h 240
   ```


### On a Windows* System Using Visual Studio* Version 2017 or Newer

#### Building the program using CMake

1. Install prerequisites. To build and run the sample you need to
   install prerequisite software and set up your environment:

   - Follow the steps in [install.md](https://github.com/intel/libvpl/blob/master/INSTALL.md) to install Intel� VPL package.
   - Visual Studio 2022 
   - [CMake](https://cmake.org)

2. Set up your environment using the following command.
   ```
   <vpl_install_dir>\etc\vpl\vars.bat
   ```
   Here `<vpl_install_dir>` represents the root folder of your Intel� VPL
   installation. If you customized the installation
   folder, the `vars.bat` is in your custom location.  Note that if a
   compiler is not installed you should run in a Visual
   Studio 64-bit command prompt.

3. Build the program using the following commands:
   ```
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

4. Run the program using the following command:
   ```
   Release\legacy-encode -i ..\..\..\content\cars_320x240.i420 -w 320 -h 240
   ```


## Running the Sample


### Example of Output

```
Implementation details:
  ApiVersion:           2.8
  Implementation type:  HW
  AccelerationMode via: D3D11
  DeviceID:             56a6/0
  Path: C:\Windows\System32\DriverStore\FileRepository\iigd_dch.inf_amd64_a35f92e9f7f89b10\libmfx64-gen.dll

Encoding ..\..\..\content\cars_320x240.i420 -> out.h265
Encoded 30 frames
```

You can find the output file `out.h265` in the build directory.

You can display the output with a video player that supports raw streams such as
FFplay. You can use the following command to display the output with FFplay:

```
ffplay out.h265
```
