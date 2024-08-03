#! /bin/sh

#for project config
#./Configure --prefix=$(pwd)/../../../out/system
#get parameter for "-j2~8 and clean"
result=$(echo "$1" | grep -Eo '*clean')
if [ "$result" = "" ];then
	mulcore_cmd=$(echo "$1" | grep '^-j[0-9]\{1,2\}$')
elif [ "$1" = "clean" ];then
	make clean
	return
elif [ "$1" = "distclean" ];then
	make clean
	return
fi

#for prject make and install
RELEASEDIR=$(pwd)/../../out/release_system/lib
RELEASEBINARY=

BUILDDIR=$(pwd)/
BUILDBINARY="libssl.so.1.0.0 libcrypto.so.1.0.0"

make $mulcore_cmd
make install_sw

#call just for buid_all.sh
if [ "$1" = "cleanthen" ] || [ "$2" = "cleanthen" ];then
	make clean
fi
#cp -r $BUILDDIR/$BUILDBINARY $RELEASEDIR
#echo $BUILDBINARY have been copy to $RELEASEDIR
