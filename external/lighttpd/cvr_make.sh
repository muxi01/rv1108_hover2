#! /bin/sh

ROOT_PATH=$(pwd)
SBIN_PATH=$ROOT_PATH/src
LIBS_PATH=$ROOT_PATH/src/.libs
CONFIGS_PATH=$ROOT_PATH/doc/config
PREFIX_PATH=/

PCRE_PATH=$ROOT_PATH/pcre
PCRE_BUILD=$ROOT_PATH/pcre/build
PCRE_LIBS=$PCRE_BUILD/lib

RELEASE_PATH=$(pwd)/../../out/system

release_lib="mod_indexfile.so mod_dirlisting.so mod_staticfile.so mod_access.so mod_cgi.so"
release_bin="lighttpd"
release_etc=
pcre_release="libpcre.so libpcre.so.0 libpcre.so.0.0.1"

##get parameter for "-j2~8 and clean"
#result=$(echo "$1" | grep -Eo '*clean')
#if [ "$result" = "" ];then
#	mulcore_cmd=$(echo "$1" | grep '^-j[0-9]\{1,2\}$')
#	
#elif [ "$1" = "clean" ];then
#	cd $PCRE_PATH && $PCRE_PATH/cvr_make.sh $1
#	cd $ROOT_PATH && make clean
#	return
#elif [ "$1" = "distclean" ];then
#	cd $PCRE_PATH && $PCRE_PATH/cvr_make.sh $1
#	cd $ROOT_PATH && make distclean
#	return
#fi

##for  project config
#result=$(find ./ -maxdepth 1 -name Makefile)
#if [ "$result" = "" ];then
#	echo "cvr_make will configure"
#    cd $ROOT_PATH && sh $(pwd)/autoconfig.sh $PCRE_BUILD $PREFIX_PATH
#fi

#cd $PCRE_PATH && $PCRE_PATH/cvr_make.sh $1
#cd $ROOT_PATH && make $mulcore_cmd

cd $SBIN_PATH && cp -r $release_bin $RELEASE_PATH/sbin/
#cd $CONFIGS_PATH && cp -r $release_etc $RELEASE_PATH/etc/
cd $LIBS_PATH && cp -r $release_lib $RELEASE_PATH/lib/
cd $PCRE_LIBS && cp -r $pcre_release $RELEASE_PATH/lib/
cd $ROOT_PATH && cp -r lighttpd.conf $RELEASE_PATH/etc/

##call just for buid_all.sh
#if [ "$1" = "cleanthen" ] || [ "$2" = "cleanthen" ];then
#	cd $PCRE_PATH && $PCRE_PATH/cvr_make.sh $1
#	cd $ROOT_PATH && make clean
#	cd $ROOT_PATH && make distclean
#fi
