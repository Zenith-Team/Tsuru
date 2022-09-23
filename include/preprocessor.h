#pragma once

// Concatenates both arguments
#define PP_CONCAT(x, y) \
    x##y

// Stringizes x
#define PP_STR(x) \
    #x

// Stringizes the value of x
#define PP_STR_VAL(x) PP_STR(x)

#define TOKENPASTE(x, y) \
    x ## y

#define TOKENPASTE2(x, y) \
    TOKENPASTE(x, y)

#define PP_ARG_N(                                     \
     _0,  _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8,  _9, \
    _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, \
    _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, \
    _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, \
    _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, \
    _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, \
    _60, _61, _62, _63, _64, N, ...) N

#define PP_EVAL_0(...) __VA_ARGS__
#define PP_EVAL_1(...) PP_EVAL_0(PP_EVAL_0(PP_EVAL_0(__VA_ARGS__)))
#define PP_EVAL_2(...) PP_EVAL_1(PP_EVAL_1(PP_EVAL_1(__VA_ARGS__)))
#define PP_EVAL_3(...) PP_EVAL_2(PP_EVAL_2(PP_EVAL_2(__VA_ARGS__)))
#define PP_EVAL_4(...) PP_EVAL_3(PP_EVAL_3(PP_EVAL_3(__VA_ARGS__)))
#define PP_EVAL(...)  PP_EVAL_4(PP_EVAL_4(PP_EVAL_4(__VA_ARGS__)))

#define PP_FOREACH_END(...)
#define PP_FOREACH_OUT
#define PP_FOREACH_COMMA ,

#define PP_FOREACH_GET_END2() 0, PP_FOREACH_END
#define PP_FOREACH_GET_END1(...) PP_FOREACH_GET_END2
#define PP_FOREACH_GET_END(...) PP_FOREACH_GET_END1
#define PP_FOREACH_NEXT0(test, next, ...) next PP_FOREACH_OUT
#define PP_FOREACH_NEXT1(test, next) PP_FOREACH_NEXT0(test, next, 0)
#define PP_FOREACH_NEXT(test, next)  PP_FOREACH_NEXT1(PP_FOREACH_GET_END test, next)

#define PP_FOREACH_0(f, x, peek, ...) f(x) PP_FOREACH_NEXT(peek, PP_FOREACH_1)(f, peek, __VA_ARGS__)
#define PP_FOREACH_1(f, x, peek, ...) f(x) PP_FOREACH_NEXT(peek, PP_FOREACH_0)(f, peek, __VA_ARGS__)

#define PP_FOREACH_LIST_NEXT1(test, next) PP_FOREACH_NEXT0(test, PP_FOREACH_COMMA next, 0)
#define PP_FOREACH_LIST_NEXT(test, next)  PP_FOREACH_LIST_NEXT1(PP_FOREACH_GET_END test, next)

#define PP_FOREACH_LIST0(f, x, peek, ...) f(x) PP_FOREACH_LIST_NEXT(peek, PP_FOREACH_LIST1)(f, peek, __VA_ARGS__)
#define PP_FOREACH_LIST1(f, x, peek, ...) f(x) PP_FOREACH_LIST_NEXT(peek, PP_FOREACH_LIST0)(f, peek, __VA_ARGS__)

/**
 * Applies the function macro `f` to each of the remaining parameters.
 * Taken from https://github.com/swansontec/map-macro/blob/master/map.h
 */
#define PP_FOREACH(f, ...) PP_EVAL(PP_FOREACH_1(f, __VA_ARGS__, ()()(), ()()(), ()()(), 0))
