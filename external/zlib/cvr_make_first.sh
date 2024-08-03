#! /bin/sh

#for project make and install
#get parameter for "-j2~8 and clean"
result=$(echo "$1" | grep -Eo '*clean')
if [ "$result" = "" ];then
	mulcore_cmd=$(echo "$1" | grep '^-j[0-9]\{1,2\}$')
elif [ "$1" = "clean" ];then
	make clean
	return
elif [ "$1" = "distclean" ];then
	make distclean
	rm Makefile
	return
fi


#for  project config
result=$(find ./ -maxdepth 1 -name Makefile)
if [ "$result" = "" ];then
	echo "cvr_make will configure"
	sh $(pwd)/autoconfig.sh
fi

RELEASEDIR=
RELEASEBINARY=

BUILDDIR=
BUILDBINARY=

make $mulcore_cmd
make install


#call just for buid_all.sh
if [ "$1" = "cleanthen" ] || [ "$2" = "cleanthen" ];then
	make distclean
	rm Makefile
fi

#cp -r $BUILDDIR/$BUILDBINARY $RELEASEDIR
#echo $BUILDBINARY have been copy to $RELEASEDIR
