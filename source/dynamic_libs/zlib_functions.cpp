#include "dynamic_libs/os_functions.h"
#include "zlib.h"

u32 zlib_handle = 0;

EXPORT_DECL(int, inflate, z_streamp strm, int flush);
EXPORT_DECL(int, inflateEnd, z_streamp strm);
EXPORT_DECL(int, deflateInit_, z_streamp strm, int level,
                               const char *version, int stream_size);
EXPORT_DECL(int, inflateInit_, z_streamp strm,
                               const char *version, int stream_size);
EXPORT_DECL(int, deflateInit2_, z_streamp strm, int  level, int  method,
                                int windowBits, int memLevel,
                                int strategy, const char *version,
                                int stream_size);
EXPORT_DECL(int, inflateInit2_, z_streamp strm, int  windowBits,
                                const char *version, int stream_size);
EXPORT_DECL(int, inflateBackInit_, z_streamp strm, int windowBits,
                                   unsigned char FAR *window,
                                   const char *version,
                                   int stream_size);

void InitAcquireZlib(void) {
    if(coreinit_handle == 0) {
        InitAcquireOS();
    };
    OSDynLoad_Acquire("zlib125.rpl", &zlib_handle);
}

extern "C" void InitZlibFunctionPointers(void) {
    u32 *funcPointer = 0;
    InitAcquireZlib();

    OS_FIND_EXPORT(zlib_handle, inflate);
    OS_FIND_EXPORT(zlib_handle, inflateEnd);
    OS_FIND_EXPORT(zlib_handle, deflateInit_);
    OS_FIND_EXPORT(zlib_handle, inflateInit_);
    OS_FIND_EXPORT(zlib_handle, deflateInit2_);
    OS_FIND_EXPORT(zlib_handle, inflateInit2_);
    OS_FIND_EXPORT(zlib_handle, inflateBackInit_);
}
