#! /bin/sh

#get parameter for "-j2~8 and clean"
result=$(echo "$1" | grep -Eo '*clean')
if [ "$result" = "" ];then
	mulcore_cmd=$(echo "$1" | grep '^-j[0-9]\{1,2\}$')
elif [ "$1" = "clean" ];then
	make clean
	return
elif [ "$1" = "distclean" ];then
	make distclean
	[ -f lib/libnl.a ] && rm lib/libnl.a
	[ -f libnl-1.pc ] && rm libnl-1.pc 
	return
fi

#for  project config
result=$(find ./ -name Makefile.opts)
if [ "$result" = "" ];then
	echo "cvr_make will configure"
	sh $(pwd)/autoconfig.sh
fi

#for project make and install
RELEASEDIR=$(pwd)/../../../out/release_system/lib
RELEASEBINARY=$RELEASEDIR/libnl.so.1.1.4

BUILDDIR=$(pwd)/lib
BUILDBINARY=libnl.so.1.1.4

make $mulcore_cmd
make install

#call just for buid_all.sh
if [ "$1" = "cleanthen" ] || [ "$2" = "cleanthen" ];then
	make distclean
	[ -f lib/libnl.a ] && rm lib/libnl.a
	[ -f libnl-1.pc ] && rm libnl-1.pc 
fi

#cp -r $BUILDDIR/$BUILDBINARY $RELEASEDIR
#echo $BUILDBINARY have been copy to $RELEASEDIR
