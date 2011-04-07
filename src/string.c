#include "string.h"

size_t strlen(const char* str)
{
	const char* sptr = str;
	for (; *sptr; sptr++);
	return sptr - str;
}

const void* memchr(const void* str, int value, size_t num)
{
	const char* sptr = (const char*)str;
	for (; *sptr; sptr++)
	{
		if (*sptr == value)
			return sptr;
		else if ((sptr - (const char*)str) > num)
			break;
	}
	return 0;
}

const char* strchr(const char* str, int c)
{
	return (const char*)memchr(str, c, strlen(str));
}

