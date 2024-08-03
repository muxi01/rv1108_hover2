#! /bin/sh

echo rockchip > /sys/class/android_usb/android0/iManufacturer
echo rk1108 > /sys/class/android_usb/android0/iProduct 

mkdir -p /dev/usb-ffs/adb
mount -t functionfs adb /dev/usb-ffs/adb
echo adb > /sys/class/android_usb/android0/f_ffs/aliases

echo 0 > /sys/class/android_usb/android0/enable
echo 2207 > /sys/class/android_usb/android0/idVendor
echo 0006 > /sys/class/android_usb/android0/idProduct
echo adb > /sys/class/android_usb/android0/functions
echo 1 > /sys/class/android_usb/android0/enable

./usr/local/sbin/adbd  &
