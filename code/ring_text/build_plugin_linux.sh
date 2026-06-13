#!/bin/bash

mkdir LinuxBinaries

TOP=$(pwd)  

chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'ringtext.so') $TOP/LinuxBinaries

cd ..

cd custom_bevel && chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'cbevel.so') $TOP/LinuxBinaries

cd ..

cd ssg && chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'ssg.so') $TOP/LinuxBinaries

cd .. 

cd port_load && chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'loadport.so') $TOP/LinuxBinaries
 
