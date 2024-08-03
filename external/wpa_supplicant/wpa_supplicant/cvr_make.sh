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

#for project make and install
RELEASEDIR=
RELEASEBINARY=

BUILDDIR=
BUILDBINARY=

make $mulcore_cmd
make install

#call just for buid_all.sh
if [ "$1" = "cleanthen" ] || [ "$2" = "cleanthen" ];then
	make clean
fi

#cp -r $BUILDDIR/$BUILDBINARY $RELEASEDIR
#echo $BUILDBINARY have been copy to $RELEASEDIR
