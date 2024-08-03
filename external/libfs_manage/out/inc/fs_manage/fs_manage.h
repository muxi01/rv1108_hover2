#ifndef __FS_MANAGE_H__
#define __FS_MANAGE_H__

int64_t fs_manage_lseek(int fd,int64_t offset ,int whence);
ssize_t fs_manage_read(int fd, void *buf, size_t count);
ssize_t fs_manage_write(int fd, const void *buf, size_t count);
int fs_manage_open(const char *filename, int flags, ...);
int fs_manage_close(int fd);
FILE * fs_manage_fopen(const char * file_name, const char * mode);
int fs_manage_fclose(FILE *fp);
int fs_manage_writetrail(int fd);
int fs_manage_blocknotify(int prev_num, int later_num, char *filename);
int fs_manage_fstat(int fd, struct stat *filestat);


#endif
