// Misc. utility C++ functions

#include <stdio.h>
#include <string.h>
#include <cstdarg>

#include <dynlibs/os/functions.h>
#include <types.h>

// Compare if two strings are equal
extern "C" int strcmp(const char* str1, const char* str2) {
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
extern "C" int wcscmp(const wchar_t* str1, const wchar_t* str2) {
    while (*str1 == *str2++)
        if (*str1++ == 0) 
            return 0;

    return (*str1 - *--str2);
}
