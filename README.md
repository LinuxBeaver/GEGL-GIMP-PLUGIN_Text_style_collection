
Download here.
https://github.com/LinuxBeaver/Gimp-Misc-Bevel-Collection-Plugin/releases

## Misc Bevel Bump Collection - Gimp Plugin

Currently 24 different bevel bump map variations exist for the user to choose from with like 11 or 13 debatably unique filters all in one place. That way instead of giving all these crazy bevels and bumps their own plugin they can all be grouped in one place. Yes, I know the cake text is based

![image](https://github.com/LinuxBeaver/GIMP_Misc_Bevel_Collection_super_pluginWORK_IN_PROGRESS/assets/78667207/f20ab112-f8cd-48ad-8dd8-b62a6ede37cb)

![image](https://github.com/LinuxBeaver/GIMP_Misc_Bevel_Collection_super_pluginWORK_IN_PROGRESS/assets/78667207/0e8b1a26-8787-4675-9123-a79b85d5e45c)


![image](https://github.com/LinuxBeaver/GIMP_Misc_Bevel_Collection_super_pluginWORK_IN_PROGRESS/assets/78667207/13483f98-8ecf-4a14-8f74-3e98793e75cb)

## OS specific location to put GEGL Filter binaries 

**Windows**
C:\Users\USERNAME\AppData\Local\gegl-0.4\plug-ins
 
** Linux **
 /home/(USERNAME)/.local/share/gegl-0.4/plug-ins
 
 **Linux (Flatpak)**
 /home/(USERNAME)/.var/app/org.gimp.GIMP/data/gegl-0.4/plug-ins

![image](https://github.com/LinuxBeaver/GEGL-glossy-balloon-text-styling/assets/78667207/f15fb5eb-c8d7-4c08-bbac-97048864e657)


## Compiling and Installing
**Linux**

To compile and install you will need the GEGL header files (libgegl-dev on Debian based distributions or gegl on Arch Linux) and meson (meson on most distributions).

meson setup --buildtype=release build
ninja -C build


If you have an older version of gegl you may need to copy to ~/.local/share/gegl-0.3/plug-ins instead (on Ubuntu 18.04 for example).

**Windows**

The easiest way to compile this project on Windows is by using msys2. Download and install it from here: https://www.msys2.org/

Open a msys2 terminal with C:\msys64\mingw64.exe. Run the following to install required build dependencies:

pacman --noconfirm -S base-devel mingw-w64-x86_64-toolchain mingw-w64-x86_64-meson mingw-w64-x86_64-gegl

Then build the same way you would on Linux:

meson setup --buildtype=release build
ninja -C build


## Let's see more previews starting with Cake Text

![image](https://github.com/LinuxBeaver/GIMP_Misc_Bevel_Collection_super_pluginWORK_IN_PROGRESS/assets/78667207/c6c8e817-913f-46a6-a48f-61e8ee459984)

![image](https://github.com/LinuxBeaver/GIMP_Misc_Bevel_Collection_super_pluginWORK_IN_PROGRESS/assets/78667207/ade1daef-12d4-4375-abd2-908a5948afa0)

## A bevel that only bevels edges
![image](https://github.com/LinuxBeaver/GIMP_Misc_Bevel_Collection_super_pluginWORK_IN_PROGRESS/assets/78667207/f59fc39f-5293-4389-9c86-6bc4b216300c)

## a gold and wax text graph I made in last year is finally a plugin
![image](https://github.com/LinuxBeaver/Gimp-Misc-Bevel-Collection-Plugin/assets/78667207/b488d95c-3b8c-42ba-a327-337b646c0e0f)
![image](https://github.com/LinuxBeaver/Gimp-Misc-Bevel-Collection-Plugin/assets/78667207/197bbee5-9c15-48ea-a6e5-e1480be58c96)

## Ringed Gold Text and Glossy Balloon

![image](https://github.com/LinuxBeaver/Gimp-Misc-Bevel-Collection-Plugin/assets/78667207/a6d29433-ad03-473c-a826-0312d0e5451a)

![image](https://github.com/LinuxBeaver/Gimp-Misc-Bevel-Collection-Plugin/assets/78667207/d38ca871-e256-4e36-a438-c6918578fa86)

## cake again (because its so cool :D)
![image](https://github.com/LinuxBeaver/Gimp-Misc-Bevel-Collection-Plugin/assets/78667207/4e55b4d7-7645-47d7-94bd-c7b08c6e7fe4)


Enjoy
