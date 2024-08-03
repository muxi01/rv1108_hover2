#! /bin/sh

#get parameter for "-j2~8 and clean"
result=$(echo "$1" | grep -Eo '*clean')
if [ "$result" = "" ];then
	mulcore_cmd=$(echo "$1" | grep '^-j[0-9]\{1,2\}$')
elif [ "$1" = "clean" ];then
	return
elif [ "$1" = "distclean" ];then
	return
fi

CFLAGS="-I$(pwd)/../../out/system/include" \
CPPFLAGS="-g -I$(pwd)/../../out/system/include " \
CXXFLAGS="-g -I$(pwd)/../../out/system/include" \
arm-linux-gcc  -fPIC -O3 -o fsck_modos main.c  boot.c check.c dir.c fat.c -L$(pwd)/../../out/system/lib -I$(pwd)/../../out/system/include

RELEASEDIR=$(pwd)/../../out/system/sbin
RELEASEBINARY=

BUILDDIR=$(pwd)
BUILDBINARY=$BUILDDIR/fsck_modos

#cp $BUILDBINARY $SYSTEMDIR
cp $BUILDBINARY $RELEASEDIR 
rm $BUILDBINARY
