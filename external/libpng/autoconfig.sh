#! /bin/sh
export CFLAGS="-I$(pwd)/../../out/system/include"
export CPPFLAGS="-I$(pwd)/../../out/system/include"
export CXXFLAGS="-I$(pwd)/../../out/system/include" 
export LDFLAGS="-L$(pwd)/../../out/system/lib"
./configure --prefix=$(pwd)/../../out/system CC=arm-linux-gcc --host=arm-linux
