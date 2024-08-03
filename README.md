CPU：RV1108G
RAM：128MB
FLASH：SPI NOR / GD25Q256e 32MB
WIFI：AR1021X
屏幕：240x240
电池：未知mAh
系统：Linux3.10
大气压计：DSP310 I2C3 地址 0x76
地磁传感器：IST8310 I2C1 地址 0x0E
IMU: ICM20602 /dev/spi0
GNSS模块：/dev/ttyS0 波特率：115200
按键：已经适配好，通过evtest可以读到键值
侧边编码器：已经适配好，通过evtest可以读到键值
摇杆：cat /sys/bus/iio/devices/iio:device0/in_voltage*_raw 根据ADC值判断
波轮：cat /sys/bus/iio/devices/iio:device0/in_voltage*_raw 根据ADC值判断
