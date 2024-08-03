#!/bin/bash
DIR_IMAGE=../../rockimg/Image-cvr

sudo ./upgrade_tool db ../CVRTools_Release_v1.00/Image/RK1108_usb_boot.bin
sudo ./upgrade_tool wl 0 ${DIR_IMAGE}/Firmware.img
sudo ./upgrade_tool rd
