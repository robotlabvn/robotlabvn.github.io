---
layout: post
category: blog
title: Installing librealsense for T265 on various compute platforms
snippet: Attempting to install librealsense on various small compute platforms (Intel Aero UAV, Odroid XU4, Nvidia TX2)
tags: [robotics, hardware]
---
This work was done in collaboration with [Alex Spitzer](http://alexspitzer.com).

-------------

Librealsense Linux installation instructions can be found  [here](https://github.com/IntelRealSense/librealsense/blob/master/doc/distribution_linux.md). Check the installation page for OS/kernel compatibilities. 

#### What does a successful installation look like?
- `lsusb`: One of the entries should be: `Bus 002 Device 00X: ID 8087:0b37 Intel Corp. `
- `dmesg`: will contain a snippet that should look like:

  ```
  [15345.891625] usb 2-1: new SuperSpeed USB device number X using xhci_hcd
  [15345.912410] usb 2-1: New USB device found, idVendor=8087, idProduct=0b37
  [15345.912413] usb 2-1: New USB device strings: Mfr=1, Product=2, SerialNumber=3
  [15345.912415] usb 2-1: Product: Intel(R) RealSense(TM) Tracking Camera T265
  [15345.912417] usb 2-1: Manufacturer: Intel(R) Corporation
  [15345.912419] usb 2-1: SerialNumber: 9092121111230000
  ```
- run `rs-enumerate-devices`, this should output:

  ```
  Device info:
  Name : Intel RealSense T265
  Serial Number : 909212111123
  Firmware Version : 0.0.18.5715
  Physical Port : vid_8087 pid_0B37 bus_2 port_1
  Product Id : 0B37
  Product Line : T200

  Stream Profiles supported by Tracking Module
  Supported modes:
  stream resolution fps format
  Fisheye 1 848x800 @ 30Hz Y8
  Fisheye 2 848x800 @ 30Hz Y8
  Gyro N/A @ 200Hz MOTION_XYZ32F
  Accel N/A @ 62Hz MOTION_XYZ32F
  Pose N/A @ 200Hz 6DOF
  ```

- Launch `realsense-viewer` and your T265 should be detected.

#### What does an unsuccessful connection look like?
- `lsusb`: One of the output will be registered as `Bus 001 Device 00X: ID 03e7:2150`
- `dmesg`: will output something similar to:

```
[15207.515371] usb 1-1: new high-speed USB device number 7 using xhci_hcd
[15207.664270] usb 1-1: New USB device found, idVendor=03e7, idProduct=2150
[15207.664276] usb 1-1: New USB device strings: Mfr=1, Product=2, SerialNumber=3
[15207.664280] usb 1-1: Product: Movidius MA2X5X
[15207.664283] usb 1-1: Manufacturer: Movidius Ltd.
[15207.664286] usb 1-1: SerialNumber: 03e72150
```

- `rs-enumerate-devices` outputs no device found


#### Resetting the T265 connection

If you encounter an unsuccessful connection by checking all three above, you should be able to reset the T265 by running `realsense-viewer` or `rs-pose`, then checking the above three commands again. If the output doesn't change for all three, this indicates an installation failure. 


If you have an unsuccessful installation, [you're not the only one](https://github.com/IntelRealSense/librealsense/issues/3361)! We tried installing librealsense on two common constrained compute systems (Odroid XU4, Nvidia TX2) and an OTS UAV (Intel Aero).


-------------

## Intel Aero: Unsuccessful

Intel Aero platform works with Ubuntu 16.04 (and [cannot be upgraded]( https://github.com/intel-aero/meta-intel-aero/wiki/90-(References)-OS-user-Installation)), and uses kernel version 4.4.76-aero1.2, a custom kernel. The aero's customized kernel is required to communicate to the onboard flight controller. Unfortunately, the Intel Aero platform is [discontinued as of Feb. 2019](https://github.com/IntelRealSense/librealsense/issues/3323), so if you are hoping they're going to update their kernel to work with librealsense, you're out of luck.
However, we tried to build librealsense with the following kernels on Ubuntu 16.04 with both prebuild packages and source to see if it would work:

- 4.4.76-aero1.2: No success. 
- 4.10-generic: No success.
- 4.15-generic: USB port no longer detects a device. This version of the kernel probably doesn't work with the Intel Aero.

For these unsuccessful installations, the following messages are encountered in the build step after running `sudo apt-get install librealsense2-dkms librealsense2-utils`:


-------------

## Odroid XU4: Successful

To install librealsense on Odroid (Ubuntu 18.04 LTS, kernel v4.14), install from source by following [these instructions](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation.md) with [fixes](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation_odroid.md).

Note that, the supported versions of librealsense is 4.{4, 8, 10, 13, 15, 16} while the two supported kernel versions of odroid XU4 is 4.9 [(discontinued LTS support) and 4.14 (current LTS support)](https://com.odroid.com/sigong/blog/blog_list.php?bid=192). However, the fix for Odroid indicates that installation of librealsense [is possible on kernel version 4.14](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation_odroid.md), so follow those instructions, with the following caveats:

- Make sure that your kernel version is 4.14 (`uname -r` should output Linux odroid 4.14). If not, upgrade your kernel as outlined in the installation guide by doing:

```
sudo apt-get update && sudo apt-get upgrade && sudo apt-get dist-upgrade
```

- The patch file `patch-realsense-odroid.sh` isn't there, but there are two other patch files in the scripts folder:
  - `./scripts/patch-realsense-ubuntu-odroid-xu4-4.14.sh`
  - `./scripts/patch-realsense-ubuntu-odroid.sh`

 As of today, `patch-realsense-ubuntu-odroid-xu4-4.14.sh` was last updated 8 months ago vs. a year ago, so I used that one. 

- Follow the TM1 specific instructions in Step 5 in "Prepare Linux Backend and the Dev. Environment" since we're interested in the tracking module.

- After following instructions to prepare the Linux backend, all you have to do is build the packages, but make sure to add the flag `-DBUILD_WITH_TM2=true` to the end of your cmake command, as such:


```
cmake ../ -DBUILD_EXAMPLES=true -DBUILD_WITH_TM2=true
```


This is important to get the T265 working. 

- Confirm your installation with either `rs-pose` or `realsense-viewer` (requires a graphical display).

After, feel free to install realsense-ros as usual. If you're using Ubuntu 18.04, The required package `ddynamic_configure` needs to be cloned manually into your workspace/src folder. Clone the `kinetic-devel` version from [here](https://github.com/pal-robotics/ddynamic_reconfigure/tree/kinetic-devel).


-------------

## Nvidia Jetson TX2: Successful

We're working with a Nvidia Jetson TX2 with an Auvidea J120 carrier board, where it has Ubuntu 18.04 LTS with kernel version 4.9.140.

The TX2 uses an arm architecture, which means that you won't be able to install from prebuild binaries. If you attempt, you will probably see this error:

```
W: Skipping acquire of configured file 'main/binary-arm64/Packages' as repository
'http://realsense-hw-public.s3.amazonaws.com/Debian/apt-repo bionic InRelease'
doesn't support architecture 'arm64'
```

#### Build from source

To install librealsense on TX2 (Ubuntu 18.04 LTS, kernel v4.9.140), follow [these instructions](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation.md) with the following caveats:

- You can attempt to upgrade to one of the supported kernel versions (4.{4, 8, 10, 13, 15, 16}) before continuing build with source. Attempting to upgrade to the newest (`sudo apt install linux-image-4.15.0-54-generic`) didn't succeed and threw an "unsupported platform" message.
- Skip Step 4 in "Prepare Linux Backend and the Dev. Environment".
- Follow the TM1 specific instructions in Step 5 in "Prepare Linux Backend and the Dev. Environment" since we're interested in the tracking module.
- After following instructions to prepare the Linux backend, all you have to do is build the packages, but make sure to add the flag `-DBUILD_WITH_TM2=true` to the end of your cmake command, as such:


```
cmake ../ -DBUILD_EXAMPLES=true -DBUILD_WITH_TM2=true
```

This is important to get the T265 working. 

- Confirm your installation with either `rs-pose` or `realsense-viewer` (requires a graphical display).

After, feel free to install realsense-ros as usual. If you're using Ubuntu 18.04, The required package `ddynamic_configure` needs to be cloned manually into your workspace/src folder. Clone the `kinetic-devel` version from [here](https://github.com/pal-robotics/ddynamic_reconfigure/tree/kinetic-devel).


-------------

Special thanks to [Aditya Dhawale](https://adityand.wordpress.com/) and [Cherie Ho](http://cherieho.com) for enlightened conversations about this effort.
