#ifndef __FS_USERDATA_H__
#define __FS_USERDATA_H__

#define USERDATA_DEVICE "/dev/userdata"


int fs_userdata_exist(); // 1 exist 0 none
int fs_userdata_get_filesize(char *filename);
int fs_userdata_write(char *filename, char *buffer, int buffer_size);
int fs_userdata_read(char *filename, char *buffer, int buffer_size);
int fs_userdata_init();
int fs_userdata_deinit();
char* fs_userdata_next_filename(char *filename);
int fs_userdata_deletefile(char *filename);

#endif
