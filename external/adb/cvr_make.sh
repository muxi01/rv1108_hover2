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

arm-linux-gcc -g -rdynamic -ldl -funwind-tables -fPIC -DADB_HOST=0 -D_XOPEN_SOURCE -D_GNU_SOURCE -o adbd \
		adb.c \
		backup_service.c \
		fdevent.c \
		transport.c \
		transport_local.c \
		transport_usb.c \
		adb_auth_client.c \
		sockets.c services.c \
		file_sync_service.c \
		jdwp_service.c \
		remount_service.c \
		usb_linux_client.c \
		mincrypt/rsa.c \
		mincrypt/sha256.c \
		mincrypt/sha.c \
		-I$(pwd) -I$(pwd)/../../out/system/include -L$(pwd)/../../out/system/lib -lcutils -lpthread


SYSTEMDIR=$(pwd)/../../out/system/sbin

BUILDDIR=$(pwd)
BUILDBINARY=$BUILDDIR/adbd

cp $BUILDBINARY $SYSTEMDIR
rm $BUILDBINARY
#cp $BUILDBINARY $RELEASEDIR 
