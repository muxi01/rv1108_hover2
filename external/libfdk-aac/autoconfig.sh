#! /bin/sh
#CROSS_PREFIX=$(pwd)/../../../toolschain/4.4.3/bin/arm-linux-
CROSS_PREFIX=arm-linux-
./configure --prefix=$(pwd)/../../out/system \
    --host=arm-linux \
    --target=arm-linux \
    --enable-shared=yes \
    --enable-static=no \
    --with-pic=yes \
    CC="${CROSS_PREFIX}gcc" \
    CXX="${CROSS_PREFIX}g++" \
    RANLIB="${CROSS_PREFIX}ranlib" \
    AR="${CROSS_PREFIX}ar" \
    STRIP="${CROSS_PREFIX}strip" \
    NM="${CROSS_PREFIX}nm" \
    CFLAGS="-O2 -s" \
    CXXFLAGS="-O2 -s"
