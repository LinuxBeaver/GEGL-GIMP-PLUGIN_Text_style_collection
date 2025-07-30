#!/bin/bash

mkdir WindowsBinaries

TOP=$(pwd)  

chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'glossy-bevel-.dll') $TOP/WindowsBinaries

cd .. 

cd threshold_alpha2 && chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'thresholdalpha2.dll') $TOP/WindowsBinaries

cd .. 

cd port_load && chmod +x build_linux.sh

./build_linux.sh

cp $(find . -name 'loadport.dll') $TOP/WindowsBinaries
 
