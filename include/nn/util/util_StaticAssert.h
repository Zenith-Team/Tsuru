#pragma once

#ifdef __cplusplus
    #include "basis/seadTypes.h"
    #define NN_STATIC_ASSERT static_assert
#else
    #define NN_STATIC_ASSERT ((void)0)
#endif

#define NN_STATIC_ASSERT_IS_POD(T) ((void)0)
