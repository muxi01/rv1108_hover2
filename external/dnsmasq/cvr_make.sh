#! /bin/sh

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

RELEASEDIR=$(pwd)/../../../out/release_system/sbin
RELEASEBINARY=

BUILDDIR=$(pwd)/src
BUILDBINARY="dnsmasq"

make $mulcore_cmd
make install

#call just for buid_all.sh
if [ "$1" = "cleanthen" ] || [ "$2" = "cleanthen" ];then
	make clean
fi
#cp -r $BUILDDIR/$BUILDBINARY $RELEASEDIR
#echo $BUILDDIR/$BUILDBINARY have been copy to $RELEASEDIR
