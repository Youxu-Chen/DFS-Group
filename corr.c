#include "corr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char _path_buffer[MAX_PATH_LEN + 6] = "user.";	// "user." and the last '\0' takes 6 bytes of space

void _set_xattr_name(const char * path)
{
	strcpy(_path_buffer, "user.");
	strcat(_path_buffer, path);
}

ssize_t corr_list(const char * file_path, char * buffer, size_t len)
{
	char * _buf = (char *) calloc (len, sizeof(char));
	
	// size: length of buffering list "_buf"
	ssize_t size = listxattr(file_path, _buf, len);
	if (size < 0)	return size;

	// find total items
	long i, count = 0;
	for (i = 0; i < size; i++)
	{
		if (_buf[i] == '\0')	count++;
	}

	// according to "count", add each item into "buffer"
	char * _buf_pt = _buf;
	int _len;
	for (i = 0; i < count; i++)
	{
		sscanf(_buf_pt, "%s", _path_buffer);
		strcpy(buffer, _path_buffer + 5);

		// move pointers
		_len = strlen(_path_buffer + 5);
		_buf_pt += _len + 6;
		buffer += _len;
		*buffer = '\0';
		buffer++;
	}

	free(_buf);
	return count;
}

ssize_t corr_get(const char * file_path, const char * corr_path, uint8_t * pflag)
{
	_set_xattr_name(corr_path);
	return getxattr(file_path, _path_buffer, pflag, CORR_FLAG_LEN);
}

int corr_set(const char * file_path, const char * corr_path, uint8_t flag, int mode)
{
	_set_xattr_name(corr_path);
	return setxattr(file_path, _path_buffer, &flag, CORR_FLAG_LEN, mode);
}

int corr_rm(const char * file_path, const char * corr_path, uint8_t flag)
{
	uint8_t orig_flag;
	_set_xattr_name(corr_path);

	// Check if the correlation exists
	if (getxattr(file_path, _path_buffer, &orig_flag, CORR_FLAG_LEN) < 0)	return -1;

	// Check if no relation exists, then delete the correlation. Otherwise, update it.
	orig_flag &= ~flag;
	int ret =  orig_flag ? setxattr(file_path, _path_buffer, &orig_flag, CORR_FLAG_LEN, 0) : removexattr(file_path, _path_buffer);
	return ret;
}
