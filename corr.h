#ifndef _CORR_H_
#define _CORR_H_

#include <errno.h>		// to use errno
#include <sys/types.h>	// to use size_t

// type of flag: 8 bits
#ifndef uint8_t
#define uint8_t unsigned char
#endif

// masks for flags
#define CORR_TYPE_DATA 0x80
#define CORR_TYPE_TIME 0x40

#define CORR_LINK_DUAL 0x01

// modes
#define CORR_MODE_NORMAL 0
#define CORR_MODE_PURE_CREATE 1
#define CORR_MODE_PURE_MODIFY 2

int corr_list(const char * file_path, char * buffer, size_t len);
int corr_get(const char * file_path, const char * corr_path);
int corr_set(const char * file_path, const char * corr_path, uint8_t flag, int mode);
int corr_rm(const char * file_path, const char * corr_path, uint8_t flag);

#endif // corr.h
