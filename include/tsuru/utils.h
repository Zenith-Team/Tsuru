#pragma once

#include <types.h>

extern "C" int strcmp(const char *str1, const char *str2);
extern "C" int wcscmp(const wchar_t *str1, const wchar_t *str2);
extern "C" int snprintf(char* buffer, unsigned int length, const char* string, ...);
