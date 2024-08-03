#! /bin/sh

LIB_NAME="libdpp"
SHARE_LIB="${LIB_NAME}.so"  

# build test bin
cd test
make
cd ..

# copy the source to out path
echo "Dpp include file and .so copy starting..."
SYSTEM_OUT_PATH="$(pwd)/../../out" 
if [ ! -d "$SYSTEM_OUT_PATH/system/lib" ];then
echo "Copy share library failed, please compile system!"
else
cp $(pwd)/out/lib/$SHARE_LIB $SYSTEM_OUT_PATH/system/lib
if [ ! -d "$SYSTEM_OUT_PATH/system/include/dpp" ];then
mkdir $SYSTEM_OUT_PATH/system/include/dpp
fi
if [ ! -d "$SYSTEM_OUT_PATH/system/bin" ];then
echo "Copy test binary failed, please compile system!"
else
cp $(pwd)/test/dsp_test $SYSTEM_OUT_PATH/system/bin
fi

# Copy dsp firmware
if [ ! -d "$SYSTEM_OUT_PATH/system/firmware" ];then
mkdir -p $SYSTEM_OUT_PATH/system/firmware
fi
cp $(pwd)/out/firmware/rkdsp.bin $SYSTEM_OUT_PATH/system/firmware

cp -r $(pwd)/out/inc/*  $SYSTEM_OUT_PATH/system/include/dpp
fi
echo "Done"
