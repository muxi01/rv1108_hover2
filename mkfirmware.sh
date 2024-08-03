TOOL_PATH=$(pwd)/build
IMAGE_OUT_PATH=$(pwd)/rockimg/Image-cvr
IMAGE_RELEASE_PATH=$(pwd)/rockimg/Image-release
KERNEL_PATH=$(pwd)/kernel
product=$1

if [ "$product" = "" ];then
	echo "Package firmware fail, please input product version, such as "rk1108-cvr""
	exit
fi

echo "Package rootfs.img now"
source $(pwd)/build/mkrootfs.sh

echo "Package firmware.img now"
cat $KERNEL_PATH/arch/arm/boot/zImage $KERNEL_PATH/arch/arm/boot/dts/$product.dtb > $KERNEL_PATH/zImage-dtb
$TOOL_PATH/kernelimage --pack --kernel $KERNEL_PATH/zImage-dtb $KERNEL_PATH/kernel.img 0x62000000 > /dev/null && \
rm -f $KERNEL_PATH/zImage-dtb
echo 'Image: kernel image is ready'

cp $KERNEL_PATH/kernel.img $IMAGE_OUT_PATH
cp $IMAGE_RELEASE_PATH/rk1108loader.bin $IMAGE_OUT_PATH
cp $IMAGE_RELEASE_PATH/rk1108ddr.bin $IMAGE_OUT_PATH
$TOOL_PATH/firmwareMerger -p  $TOOL_PATH/setting.ini $IMAGE_OUT_PATH/
