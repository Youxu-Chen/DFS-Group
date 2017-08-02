#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "corr.h"

#define TEST_A "dir/a"
#define TEST_B "dir/b"
#define TEST_C "dir/c"

void error_out()
{
	printf("Error caught: code %d (%s)\n", errno, strerror(errno));
}

int main()
{
	char list_buffer[1024] = { 0 }; // used to hold paths of all the correlational files
	char corr_buffer[1024] = { 0 };	// used to get the correlational file path
	
	printf("In the beginning, correlation total: %ld\n\n", corr_list(TEST_A, list_buffer, 1024));

	if (corr_set(TEST_A, TEST_B, CORR_TYPE_DATA | CORR_LINK_DUAL, CORR_MODE_NORMAL) < 0)
	{
		error_out();
		return 0;
	}

	if (corr_set(TEST_A, TEST_C, CORR_TYPE_TIME | CORR_LINK_NONREVERSING, CORR_MODE_NORMAL) < 0)
	{
		error_out();
		return 0;
	}

	printf("After adding the correlation between a and b, we can get it as following:\n");

	ssize_t size = corr_list(TEST_A, list_buffer, 1024);
	if (size < 0)
	{
		error_out();
		return 0;
	}

	char * list_pt = list_buffer;
	long i;
	uint8_t flag;
	for (i = 0; i < size; i++)
	{
		sscanf(list_pt, "%s", corr_buffer);
		list_pt += strlen(corr_buffer) + 1;
		if (corr_get(TEST_A, corr_buffer, &flag) < 0)
		{
			error_out();
			return 0;
		}
		printf("File %s: 0x%X\n", corr_buffer, flag);
	}

	if (corr_rm(TEST_A, TEST_B, CORR_TYPE_DATA | CORR_LINK_DUAL) < 0)
	{
		error_out();
		return 0;
	}

	if (corr_rm(TEST_A, TEST_C, CORR_TYPE_TIME | CORR_LINK_NONREVERSING) < 0)
	{
		error_out();
		return 0;
	}

	printf("\n\nAfter deleting the correlation, correlation total: %ld\n\n", corr_list(TEST_A, list_buffer, 1024));

	return 0;
}
