#ifndef _CORR_H_
#define _CORR_H_

#include <sys/types.h>	// to use size_t
#include <attr/xattr.h>

// type of flag: 8 bits
#ifndef uint8_t
#define uint8_t unsigned char
#endif

#define CORR_FLAG_LEN 8

// maximum length of path
#define MAX_PATH_LEN 4096

// masks for flags
#define CORR_TYPE_DATA 0x80
#define CORR_TYPE_TIME 0x40

#define CORR_LINK_NONREVERSING 0x00
#define CORR_LINK_DUAL 0x01

// modes
#define CORR_MODE_NORMAL 0
#define CORR_MODE_PURE_CREATE XATTR_CREATE
#define CORR_MODE_PURE_MODIFY XATTR_REPLACE

ssize_t corr_list(const char * file_path, char * buffer, size_t len);
ssize_t corr_get(const char * file_path, const char * corr_path, uint8_t * pflag);
int corr_set(const char * file_path, const char * corr_path, uint8_t flag, int mode);
int corr_rm(const char * file_path, const char * corr_path, uint8_t flag);

#endif // corr.h
