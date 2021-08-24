// Misc. utility C++ functions

#include <stdio.h>
#include <string.h>
#include <cstdarg>

#include <dynlibs/os/functions.h>

// Compare if two strings are equal
extern "C" int strcmp(const char *str1, const char *str2) {
    const unsigned char* s1 = (const unsigned char*)str1;
    const unsigned char* s2 = (const unsigned char*)str2;
    unsigned char c1, c2;

    do {
        c1 = (unsigned char)*s1++;
        c2 = (unsigned char)*s2++;
        if (c1 == '\0') return c1 - c2;
    } while (c1 == c2);

    return c1 - c2;
}

// Compare if two wide strings are equal
extern "C" int wcscmp(const wchar_t *str1, const wchar_t *str2) {
    while (*str1 == *str2++)
        if (*str1++ == 0) 
            return 0;

    return (*str1 - *--str2);
}

// Implementation for C snprintf
extern "C" int snprintf(char* buffer, unsigned int length, const char* string, ...) {
    va_list args;
    va_start(args, string);
    int result = vsnprintf(buffer, length, string, args);
    va_end(args);
    return result;
}

// Shortcut to optimized OSBlockMove from C memcpy
inline void* memcpy(void* dst, const void* src, size_t size) {
    return OSBlockMove(dst, src, size, 0);
}

// Shortcut to optimized OSBlockSet from C memset
inline void* memset(void* dst, unsigned char value, size_t size) {
    return OSBlockSet(dst, value, size);
}

