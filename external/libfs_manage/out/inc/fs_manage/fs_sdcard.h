#ifndef __FS_SDCARD_H__
#define __FS_SDCARD_H__

#define SDCARD_PATH	    "/mnt/sdcard"
#define SDCARD_DEVICE   "/dev/mmcblk0"
#define SDCARD_PARTITION   "/dev/mmcblk0p1"

typedef enum _FILESYSTYPE {
	VFAT = 0,
	EXFAT,
	EXT2,
	EXT3,
	EXT4,
	UNSUPPROT
}FILESYSTYPE;

typedef enum _FORMATTYPE {
	FORMAT_NORMAL = 0,
	FORMAT_SPECICAL
}FORMATTYPE;


int fs_manage_sd_exist(const char *sdcard_path);
int fs_manage_sdcard_mount();
int fs_manage_sdcard_unmount();
int fs_manage_format_sdcard(int (*callback)(void *), void *arg, int type);
int fs_manage_checksdcardcapacity(long long *free_size, long long *total_size, int *fblock_size);
void fs_manage_set_device(const char *sdcard_device);
char * fs_manage_get_device();

#endif

