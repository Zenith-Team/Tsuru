#ifndef __OS_DEFS_H_
#define __OS_DEFS_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _OsSpecifics {
    unsigned int addrOSDynLoadAcquire;
    unsigned int addrOSDynLoadFindExport;
    unsigned int addrOSTitleMainEntry;

    unsigned int addrKernSyscallTbl1;
    unsigned int addrKernSyscallTbl2;
    unsigned int addrKernSyscallTbl3;
    unsigned int addrKernSyscallTbl4;
    unsigned int addrKernSyscallTbl5;
} OsSpecifics;

typedef struct _sMemArea {
    unsigned int        address;
    unsigned int        size;
    struct _sMemArea* next;
} sMemArea;

#ifdef __cplusplus
}
#endif

#endif // __OS_DEFS_H_
