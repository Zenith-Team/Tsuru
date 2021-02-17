#pragma once

// Concatenates both arguments
#define PP_CONCAT(x, y) x##y

// Stringizes x
#define PP_STR(x) #x

// Stringizes the value of x
#define PP_STR_VAL(x) PP_STR(x)


#define PP_ARG_N( \
     _0,  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, \
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
    _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
    _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
    _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
    _60, _61, _62, _63, _64,   N, ...)   N

#define PP_RSEQ                             \
    64, 63, 62, 61, 60, 59, 58, 57, 56, 55, \
    54, 53, 52, 51, 50, 49, 48, 47, 46, 45, \
    44, 43, 42, 41, 40, 39, 38, 37, 36, 35, \
    34, 33, 32, 31, 30, 29, 28, 27, 26, 25, \
    24, 23, 22, 21, 20, 19, 18, 17, 16, 15, \
    14, 13, 12, 11, 10,  9,  8,  7,  6,  5, \
     4,  3,  2,  1,  0


// Returns number of arguments (range: 0-64)
#define PP_NARG(...) \
    PP_NARG_(0, ## __VA_ARGS__, PP_RSEQ)

#define PP_NARG_(...) \
    PP_ARG_N(__VA_ARGS__)


// foreach for specific argument counts
#define PP_FOR_EACH_0(M, X, ...)
#define PP_FOR_EACH_1(M, X, ...) M(X)
#define PP_FOR_EACH_2(M, X, ...) M(X) PP_FOR_EACH_1(M, __VA_ARGS__)
#define PP_FOR_EACH_3(M, X, ...) M(X) PP_FOR_EACH_2(M, __VA_ARGS__)
#define PP_FOR_EACH_4(M, X, ...) M(X) PP_FOR_EACH_3(M, __VA_ARGS__)
#define PP_FOR_EACH_5(M, X, ...) M(X) PP_FOR_EACH_4(M, __VA_ARGS__)
#define PP_FOR_EACH_6(M, X, ...) M(X) PP_FOR_EACH_5(M, __VA_ARGS__)
#define PP_FOR_EACH_7(M, X, ...) M(X) PP_FOR_EACH_6(M, __VA_ARGS__)
#define PP_FOR_EACH_8(M, X, ...) M(X) PP_FOR_EACH_7(M, __VA_ARGS__)
#define PP_FOR_EACH_9(M, X, ...) M(X) PP_FOR_EACH_8(M, __VA_ARGS__)
#define PP_FOR_EACH_10(M, X, ...) M(X) PP_FOR_EACH_9(M, __VA_ARGS__)
#define PP_FOR_EACH_11(M, X, ...) M(X) PP_FOR_EACH_10(M, __VA_ARGS__)
#define PP_FOR_EACH_12(M, X, ...) M(X) PP_FOR_EACH_11(M, __VA_ARGS__)
#define PP_FOR_EACH_13(M, X, ...) M(X) PP_FOR_EACH_12(M, __VA_ARGS__)
#define PP_FOR_EACH_14(M, X, ...) M(X) PP_FOR_EACH_13(M, __VA_ARGS__)
#define PP_FOR_EACH_15(M, X, ...) M(X) PP_FOR_EACH_14(M, __VA_ARGS__)
#define PP_FOR_EACH_16(M, X, ...) M(X) PP_FOR_EACH_15(M, __VA_ARGS__)

// foreach with argument count as first argument (range: 0-16)
#define PP_FOR_EACH_N(N, M, ...) \
    PP_CONCAT(PP_FOR_EACH_, N)(M, __VA_ARGS__)

// Applies M to all arguments (count range: 0-16)
#define PP_FOR_EACH(M, ...) \
    PP_FOR_EACH_N(PP_NARG(__VA_ARGS__), M, __VA_ARGS__)
