;db�����ʾ����boot
db Image\RK1108Loader_V1.10.bin
;wd�����ʾ�ȴ��豸,����Ϊ0�ǵȴ�maskrom�豸,Ϊ1�ǵȴ�loader�豸
wd 0
;wl�����ǰ�lbaд�ļ�,��1��������ƫ�ƣ���2���������ļ�·��
wl 0x10000000 ..\..\rockimg\Image-cvr\Firmware.img
rd 1
