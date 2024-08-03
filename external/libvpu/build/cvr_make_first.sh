#! /bin/sh

BUILD_DIR=$(pwd)/../out
BUILD_LIB_DIR=$BUILD_DIR/lib
BUILD_INC_DIR=$BUILD_DIR/inc
#BUILD_BIN_DIR=$BUILD_DIR/bin

SYSTEM_DIR=$(pwd)/../../../out/system
SYSTEM_LIB_DIR=$SYSTEM_DIR/lib
#SYSTEM_BIN_DIR=$SYSTEM_DIR/bin
SYSTEM_INC_DIR=$SYSTEM_DIR/include/mpp


#get parameter for "-j2~8 and clean"
result=$(echo "$1" | grep -Eo '*clean')
if [ "$result" = "" ];then
	mulcore_cmd=$(echo "$1" | grep '^-j[0-9]\{1,2\}$')
elif [ "$1" = "clean" ];then
	return
elif [ "$1" = "distclean" ];then
	return
fi

# copy the source to out path

[ ! -d "$SYSTEM_LIB_DIR" ] && mkdir $SYSTEM_LIB_DIR
[ ! -d "$SYSTEM_INC_DIR" ] && mkdir $SYSTEM_INC_DIR
#[ ! -d "$SYSTEM_BIN_DIR" ] && mkdir $SYSTEM_BIN_DIR

cd $BUILD_LIB_DIR && cp -r     *    $SYSTEM_LIB_DIR
#cd $BUILD_BIN_DIR && cp -r     *    $SYSTEM_BIN_DIR
cd $BUILD_INC_DIR && cp -r     *    $SYSTEM_INC_DIR

echo "libvpu Done"
