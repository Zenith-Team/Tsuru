#ifndef __ZLIB_FUNCTIONS_H_
#define __ZLIB_FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "zlib.h"

extern unsigned int zlib_handle;

void InitZlibFunctionPointers(void);
void InitAcquireZlib(void);

extern int (*inflate)(z_streamp strm, int flush);
extern int (*inflateEnd)(z_streamp strm);

extern int (*deflateInit_)(z_streamp strm, int level,
                           const char *version, int stream_size);
extern int (*inflateInit_)(z_streamp strm,
                           const char *version, int stream_size);
extern int (*deflateInit2_)(z_streamp strm, int  level, int  method,
                            int windowBits, int memLevel,
                            int strategy, const char *version,
                            int stream_size);
extern int (*inflateInit2_)(z_streamp strm, int  windowBits,
                            const char *version, int stream_size);
extern int (*inflateBackInit_)(z_streamp strm, int windowBits,
                               unsigned char FAR *window,
                               const char *version,
                               int stream_size);

#define deflateInit(strm, level) \
        deflateInit_((strm), (level),       ZLIB_VERSION, sizeof(z_stream))
#define inflateInit(strm) \
        inflateInit_((strm),                ZLIB_VERSION, sizeof(z_stream))
#define deflateInit2(strm, level, method, windowBits, memLevel, strategy) \
        deflateInit2_((strm),(level),(method),(windowBits),(memLevel),\
                      (strategy),           ZLIB_VERSION, sizeof(z_stream))
#define inflateInit2(strm, windowBits) \
        inflateInit2_((strm), (windowBits), ZLIB_VERSION, sizeof(z_stream))
#define inflateBackInit(strm, windowBits, window) \
        inflateBackInit_((strm), (windowBits), (window), \
                                            ZLIB_VERSION, sizeof(z_stream))

#ifdef __cplusplus
}
#endif

#endif // __ZLIB_FUNCTIONS_H_
