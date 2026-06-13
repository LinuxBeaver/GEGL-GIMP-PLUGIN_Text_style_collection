#!/bin/bash

mkdir LinuxBinaries

TOP=$(pwd)  

chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'sharpbevel.so') $TOP/LinuxBinaries

cd ..

cd edge_smooth 

chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'smoothedge.so') $TOP/LinuxBinaries

cd .. 

cd threshold_alpha2

chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'thresholdalpha2.so') $TOP/LinuxBinaries

cd .. 

cd port_load && chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'loadport.so') $TOP/LinuxBinaries
 
