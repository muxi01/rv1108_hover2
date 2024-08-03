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

arm-linux-gcc -g -rdynamic -ldl -funwind-tables -fPIC -DADB_HOST=0 -D_XOPEN_SOURCE -D_GNU_SOURCE -o tinycap \
		mixer.c  pcm.c  tinycap.c   \
		-I$(pwd)/include -I$(pwd)/../../out/system/include -L$(pwd)/../../out/system/lib -lcutils -lpthread

arm-linux-gcc -g -rdynamic -ldl -funwind-tables -fPIC -DADB_HOST=0 -D_XOPEN_SOURCE -D_GNU_SOURCE -o tinymix \
		mixer.c  pcm.c  tinymix.c   \
		-I$(pwd)/include -I$(pwd)/../../out/system/include -L$(pwd)/../../out/system/lib -lcutils -lpthread

arm-linux-gcc -g -rdynamic -ldl -funwind-tables -fPIC -DADB_HOST=0 -D_XOPEN_SOURCE -D_GNU_SOURCE -o tinypcminfo \
		mixer.c  pcm.c  tinypcminfo.c   \
		-I$(pwd)/include -I$(pwd)/../../out/system/include -L$(pwd)/../../out/system/lib -lcutils -lpthread

arm-linux-gcc -g -rdynamic -ldl -funwind-tables -fPIC -DADB_HOST=0 -D_XOPEN_SOURCE -D_GNU_SOURCE -o tinyplay \
		mixer.c  pcm.c  tinyplay.c   \
		-I$(pwd)/include -I$(pwd)/../../out/system/include -L$(pwd)/../../out/system/lib -lcutils -lpthread

SYSTEMDIR=$(pwd)/../../out/root/sbin

BUILDDIR=$(pwd)
BUILDBINARY="$BUILDDIR/tinycap  tinymix  tinyplay tinypcminfo"

cp $BUILDBINARY $SYSTEMDIR
rm $BUILDBINARY
#cp $BUILDBINARY $RELEASEDIR 
