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

arm-linux-gcc -shared -g -rdynamic -ldl -funwind-tables -fPIC -o librk_backtrace.so rk_backtrace.c -I$(pwd) -L$(pwd)/../../out/system/lib -lubacktrace


SYSTEMDIR=$(pwd)/../../out/system/lib

BUILDDIR=$(pwd)
BUILDBINARY=$BUILDDIR/librk_backtrace.so

cp $BUILDBINARY $SYSTEMDIR
rm $BUILDBINARY
#cp $BUILDBINARY $RELEASEDIR 
