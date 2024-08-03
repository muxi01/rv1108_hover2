;db命令表示下载boot
db Image\RK1108Loader_V1.10.bin
;wd命令表示等待设备,参数为0是等待maskrom设备,为1是等待loader设备
wd 0
;wl命令是按lba写文件,第1个参数是偏移，第2个参数是文件路径
wl 0x10000000 ..\..\rockimg\Image-cvr\Firmware.img
rd 1
