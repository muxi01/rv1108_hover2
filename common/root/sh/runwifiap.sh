#! /bin/sh
echo "/system/etc/firmware/fw_bcm4339a0_ag_apsta.bin" > /sys/module/bcmdhd/parameters/firmware_path 
ifconfig lo 127.0.0.1 netmask 255.255.255.0 
ifconfig wlan0 192.168.100.1 netmask 255.255.255.0 
route add -net 224.0.0.0 netmask 240.0.0.0 dev wlan0
dnsmasq -C /etc/dnsmasq.conf 
hostapd /etc/hostapd/hostapd.conf -B
