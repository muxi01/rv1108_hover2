#! /bin/bash

top_dir=$(pwd)

logfile="/dev/null"
check_cmd(){
    "$@" >> $logfile 2>&1
}
check_strip(){
  check_cmd arm-linux-strip -v
}
check_strip
if [ $? -eq 127 ];then
        export PATH=$PATH:$top_dir/prebuilts/toolschain/usr/bin
fi

#get config
source ./config/package_config.sh

TARGET_PRODUCT="CVR"
echo TARGET_PRODUCT=$TARGET_PRODUCT
TARGET="withoutkernel"
if [ "$1"x != ""x  ]; then
         TARGET=$1
fi

IMAGE_PATH=$(pwd)/out/outImage
ROOT_PATH=$(pwd)/out/root
SYSTEM_PATH=$(pwd)/out/system
TOOL_PATH=$(pwd)/build
RELEASE_SYSTEM_PATH=$IMAGE_PATH/root/usr/local
IMAGE_OUT_PATH=$(pwd)/rockimg/Image-cvr

rm -rf $IMAGE_PATH
mkdir -p $IMAGE_PATH

BOOT_OTA="ota"

#make system file
cp -R $ROOT_PATH $IMAGE_PATH

#remove exist file
[ -d $RELEASE_SYSTEM_PATH/bin ] && rm -rf $RELEASE_SYSTEM_PATH/bin
[ -d $RELEASE_SYSTEM_PATH/etc ] && rm -rf $RELEASE_SYSTEM_PATH/etc
[ -d $RELEASE_SYSTEM_PATH/lib ] && rm -rf $RELEASE_SYSTEM_PATH/lib
[ -d $RELEASE_SYSTEM_PATH/sbin ] && rm -rf $RELEASE_SYSTEM_PATH/sbin
[ -d $RELEASE_SYSTEM_PATH/share ] && rm -rf $RELEASE_SYSTEM_PATH/share
mkdir $RELEASE_SYSTEM_PATH/bin
mkdir $RELEASE_SYSTEM_PATH/etc
mkdir $IMAGE_PATH/root/lib
mkdir $RELEASE_SYSTEM_PATH/sbin
mkdir $RELEASE_SYSTEM_PATH/share

#get the bin and libary
release_bin="video wlan_service"
release_sbin="fsck_modos io"
release_lib="ld-uClibc-1.0.14.so libdl-1.0.14.so libgcc_s.so.1 libminigui_ths-3.0.so.12 libpthread.so.0 libpthread.so.1 libstdc++.so libz.so.1.2.3 ld-linux.so.3 ld-uClibc.so.1 ld-uClibc.so.0 libdl.so.2 libdl.so.1 libion.so libminigui_ths-3.0.so.12.0.0 libpng12.so libstdc++.so.6 libvpu.so libmpp.so libuClibc-1.0.14.so libfreetype.so libjpeg.so libminigui_ths.so libpng12.so.0  libstdc++.so.6.0.19 libfreetype.so.6 libjpeg.so.7 libm.so.6 libm.so.1 libpng12.so.0.37.0 libz.so libfreetype.so.6.3.20 libjpeg.so.7.0.0 libpng.so libz.so.1 libc.so.6 libc.so.1 libgcc_s.so libm-1.0.14.so  libpthread-1.0.14.so libfdk-aac.so libfdk-aac.so.1 libfdk-aac.so.1.0.0 libld.so.1 libsalsa.so.0.0.1 libsalsa.so.0 libsalsa.so libfsmanage.so libubacktrace-1.0.14.so libubacktrace.so.1 libdpp.so librk_backtrace.so libcam_hal.so libiep.so"
release_etc="MiniGUI.cfg"
release_share=

#if network function have been enable
if [[ $enable_network =~ "yes" ]];then
	echo "enable newwork"
	release_sbin="$release_sbin dnsmasq hostapd hostapd_cli"
	release_lib="$release_lib libcrypto.so libcrypto.so.1.0.0 libssl.so.1.0.0 libssl.so libnl.so.1 libnl.so.1.1.4 libnl.so librt.so.1 librt-1.0.14.so"
fi

#if wpa_supplicant function have been enable
if [[ $enable_network =~ "yes" ]] && [[ $enable_wpa =~ "yes" ]];then
	echo "enable wpa_supplicant"
	release_sbin="$release_sbin wpa_cli wpa_supplicant"
fi

#if adb function have been enable
if [[ $enable_adb =~ "yes" ]];then
	echo "enable enable_adb"
	release_sbin="$release_sbin adbd"
	release_lib="$release_lib libcutils.so"
fi

#if iperf function have been enable
if [[ $enable_iperf =~ "yes" ]];then
	echo "enable iperf"
	release_sbin="$release_sbin iperf ethtool"
	release_lib="$release_lib  libnetutils.so"
	if [[ ! $enable_adb =~ "yes" ]];then
		release_lib="$release_lib libcutils.so"
	fi
fi

#if web function have been enable
if [[ $enable_web =~ "yes" ]];then
	echo "enable web"
	release_sbin="$release_sbin lighttpd"
	release_lib="$release_lib libpcre.so libpcre.so.0 libpcre.so.0.0.1 mod_indexfile.so mod_dirlisting.so mod_staticfile.so mod_access.so mod_cgi.so"
	release_etc="$release_etc lighttpd.conf"
fi

#if iperf function have been enable
if [[ $enable_perf =~ "yes" ]];then
	echo "enable perf"
	release_sbin="$release_sbin perf"
	release_lib="$release_lib libdwfl.so  libdw.so  libebl.so  libelf.so  libperf.so"
fi

#if blktrace function have been enable
if [[ $enable_blktrace =~ "yes" ]];then
	echo "enable blktrace"
	release_sbin="$release_sbin blkparse  blktrace"
fi

#if strace function have been enable
if [[ $enable_strace =~ "yes" ]];then
	echo "enable_strace"
	release_sbin="$release_sbin strace"
fi

cp -R $SYSTEM_PATH/videofile_test $RELEASE_SYSTEM_PATH
cd $SYSTEM_PATH/bin/ && cp -r $release_bin $RELEASE_SYSTEM_PATH/bin
cd $SYSTEM_PATH/etc/ && cp -r $release_etc $RELEASE_SYSTEM_PATH/etc
cd $SYSTEM_PATH/lib/ && cp -r $release_lib $IMAGE_PATH/root/lib
cd $SYSTEM_PATH/sbin/ && cp -r $release_sbin $RELEASE_SYSTEM_PATH/sbin
cd $SYSTEM_PATH/firmware && cp * $IMAGE_PATH/root/system/etc/firmware
mkdir $RELEASE_SYSTEM_PATH/share/minigui/ && cp -R $SYSTEM_PATH/share/minigui/res $RELEASE_SYSTEM_PATH/share/minigui
mkdir $RELEASE_SYSTEM_PATH/share/sounds && cp -R $SYSTEM_PATH/share/sounds/* $RELEASE_SYSTEM_PATH/share/sounds/
chmod 777 -R $IMAGE_PATH/root
#if symbol file remove function have been enable 
if [[ $remove_symbol =~ "yes" ]];then
findfile(){
        for file in $1/*
            do
                if [ -d $file ]
                then
                    findfile $file
                elif [ -f $file ]
                then
		    # remove symbol information for reduce size	
		    #echo $file	
                    result=$(file $file)
		    [[ $result =~ "not stripped" ]] && arm-linux-strip $file
                fi
            done
}

findfile $IMAGE_PATH/root
fi

#remove useless file
FILE='.nullfiledir'
find $IMAGE_PATH -name .gitignore | sort -r > $FILE
while read line;do
   # echo "Line # $k: $line"
	rm $line 
	#echo $mk_path
	#echo $(pwd)
done < $FILE
rm $FILE

echo -n "create rootfs.img without kernel... "

# rm the rootfs.img
[ -f $IMAGE_OUT_PATH/rootfs.img ] && rm $IMAGE_OUT_PATH/rootfs.img
[ ! -d $IMAGE_OUT_PATH ] && mkdir -p $IMAGE_OUT_PATH
[ -d $IMAGE_PATH/root ] && \
$TOOL_PATH/mksquashfs  $IMAGE_PATH/root  $IMAGE_OUT_PATH/rootfs.img
echo "done."

rm -rf $IMAGE_PATH/root
