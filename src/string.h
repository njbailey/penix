
#ifndef STRING_H
#define STRING_H

#include "common.h"

typedef unsigned int size_t;

// might wanna move this stuff into common

// sizeof variable
#define sizeof(x) ((char*)(&(x) + 1) - (char*)&(x))

// sizeof type - fkn operators
#define tsizeof(t) ((char*)((t*)(1) + 1) - (char*)((t*)(1)))

size_t strlen(const char*);
const void* memchr(const void*, int, size_t);
const char* strchr(const char*, int);

#endif // STRING_H
