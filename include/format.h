#pragma once

#include "prim/seadSafeString.h"
#include "math/functions.h"

// Converts an unsigned 64 bit integer to a string
inline sead::SafeString toString64(u64 n) {
    if (!n) return sead::SafeString("0");
    char str[21] = "00000000000000000000";
    u64 div = 10000000000000000000U;
    u8 i = 0;
    while (div > 0) {
        while (n >= div) {
            n -= div;
            str[i] += 1;
        }
        i++;
        div = powi(10ULL, 19ULL - i);
    }
    char* strptr = str;
    if (strptr) while (*strptr == '0') strptr++;
    return sead::SafeString(strptr);
}

// Converts a signed 64 bit integer to a string
inline sead::SafeString toString64(s64 n) {
    if (!n) return sead::SafeString("0");
    bool negative = false;
    if (n < 0) {
        n = (18446744073709551615U - static_cast<u64>(n)) + 1;
        negative = true;
    }
    char str[22] = "+00000000000000000000";
    u64 div = 10000000000000000000U;
    u8 i = 1;
    while (div > 0) {
        while (n >= div) {
            n -= div;
            str[i] += 1;
        }
        div = powi(10ULL, 19ULL - i);
        i++;
    }
    char* strptr = str; strptr++;
    if (strptr) while (*strptr == '0') strptr++;
    if (negative) {
        strptr--;
        strptr[0] = '-';
    }
    return sead::SafeString(strptr);
}
