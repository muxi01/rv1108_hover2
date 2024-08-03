#ifndef __FS_FILEOPERA_H__
#define __FS_FILEOPERA_H__

#include <sys/types.h>
#include <time.h>

#define VIDEOFILE_PATH	"/mnt/sdcard/DCIM"
#define VIDEOHIDE_PATH	"/mnt/sdcard/DCIM/.rkhide"

#define BLOCK_FILE_TAG  "_rklock"
#define VIDEO_FILE_FORMAT  ".mp4"
#define PHOTO_FILE_FORMAT  ".jpg"

#define VIDEO_REPAIR 1
#define FILENAME_LEN 128
#define MADIASIZE_OFFSET 40
#define MAXREPAIR_FILENUM 2

#if VIDEO_REPAIR
#define REPAIR_CHECK_NUMBER 6
#define REPAIR_FILE_MINSIZE (10 * 1024)
#define REPAIR_READ_BUFFER_LEN 1024
#define REPAIR_FILE_PATH "/catch/repair_video/"
#endif

typedef enum _FILETYPE {
	VIDEOFILE_TYPE = 0,
	PICFILE_TYPE,
	LOCKFILE_TYPE
}FILETYPE;

struct file_node {
	char *name;
	time_t time;
	FILETYPE filetype;
	struct file_node *pre;
	struct file_node *next;
};


struct file_list {
	char *path;
	struct file_node *file_head;
	struct file_node *file_tail;
	struct file_node *folder_head;
	struct file_node *folder_tail;
	int usercnt;
	//int len;
};

#define COMMAND_BUFFER_SIZE 125

struct file_list *fs_manage_getfilelist(const char * path);
void fs_manage_free_filelist(struct file_list **list);
void fs_manage_getsdcardcapacity(long long *free_size, long long *total_size);
int fs_manage_remove(const char * filename);
int fs_manage_init(int (*callback)(void *), void *arg);

int fs_manage_deinit(void);

FILE * file_manage_fopen(const char * file_name, const char * mode);
int file_manage_open(const char *filename, int flags, ...);
int file_manage_fclose(FILE *fp);
int file_manage_close(int fd);
ssize_t file_manage_write(int fd, const void *buf, size_t count);
ssize_t file_manage_read(int fd, void *buf, size_t count);
int64_t file_manage_lseek(int fd,int64_t offset ,int whence);

struct file_list *fs_manage_getmediafilelist(void);
void fs_manage_free_mediafilelist(void);
int fileopera_ipcmsg_send_cmd(int fd, void *param1, void *param2, int command);
void file_manage_rename(char *filename);
void file_manage_rename_last(int number);
int file_manage_block_rename(char *filename, char *new_filename);
void fs_manage_insert_file(const char *filename);



#endif
