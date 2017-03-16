/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";

static int hello_getattr(const char *path, struct stat *stbuf)
{
    printf("Test1 /n");
	int res = 0;
printf("Test2 /n");
	memset(stbuf, 0, sizeof(struct stat));
	printf("Test3 /n");
	if (strcmp(path, "/") == 0) {
	printf("Test4 /n");
		stbuf->st_mode = S_IFDIR | 0755;
		printf("Test5 /n");
		stbuf->st_nlink = 2;
		printf("Test6 /n");
	} else if (strcmp(path, hello_path) == 0) {
	printf("Test7 /n");
		stbuf->st_mode = S_IFREG | 0444;
		printf("Test8 /n");
		stbuf->st_nlink = 1;
		printf("Test9 /n");
		stbuf->st_size = strlen(hello_str);
		printf("Test10 /n");
	} else
	printf("Test11 /n");
		res = -ENOENT;
printf("Test12 /n");
	return res;
}

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
printf("Test13 /n");
	(void) offset;
	printf("Test14 /n");
	(void) fi;
	printf("Test15 /n");

	if (strcmp(path, "/") != 0)
	printf("Test16 /n");
		return -ENOENT;
		printf("Test17 /n");

	filler(buf, ".", NULL, 0);
	printf("Test18 /n");
	filler(buf, "..", NULL, 0);
	printf("Test19 /n");
	filler(buf, hello_path + 1, NULL, 0);
	printf("Test20 /n");

	return 0;
}

static int hello_open(const char *path, struct fuse_file_info *fi)
{
printf("Test21 /n");
	if (strcmp(path, hello_path) != 0)
		return -ENOENT;
		printf("Test22 /n");

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;
printf("Test23 /n");
	return 0;
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
printf("Test24 /n");
	size_t len;
	printf("Test25 /n");
	(void) fi;
	printf("Test26 /n");
	if(strcmp(path, hello_path) != 0)
		return -ENOENT;
printf("Test27 /n");
	len = strlen(hello_str);
	printf("Test28 /n");
	if (offset < len) {
	printf("Test29 /n");
		if (offset + size > len)
			size = len - offset;
			printf("Test30 /n");
		memcpy(buf, hello_str + offset, size);
	} else
		size = 0;
		printf("Test31 /n");
printf("Test32 /n");
	return size;
}

static struct fuse_operations hello_oper = {
	.getattr	= hello_getattr,
	.readdir	= hello_readdir,
	.open		= hello_open,
	.read		= hello_read,
};

int main(int argc, char *argv[])
{
printf("Test33 /n");
	return fuse_main(argc, argv, &hello_oper, NULL);
}
