/****************************************************************************
 * Copyright (C) 2015
 * by Dimok
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any
 * damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any
 * purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you
 * must not claim that you wrote the original software. If you use
 * this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and
 * must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source
 * distribution.
 ***************************************************************************/
#include "sdk/fs/functions.h"
#include "sdk/os/functions.h"

EXPORT_DECL(s32, FSInit, void);
EXPORT_DECL(s32, FSShutdown, void);
EXPORT_DECL(s32, FSAddClient, void *pClient, s32 errHandling);
EXPORT_DECL(s32, FSAddClientEx, void *pClient, s32 unk_zero_param, s32 errHandling);
EXPORT_DECL(s32, FSDelClient, void *pClient);
EXPORT_DECL(void, FSInitCmdBlock, void *pCmd);
EXPORT_DECL(void *, FSGetCurrentCmdBlock, void *pClient);
EXPORT_DECL(s32, FSGetMountSource, void *pClient, void *pCmd, s32 type, void *source, s32 errHandling);

EXPORT_DECL(s32, FSMount, void *pClient, void *pCmd, void *source, char *target, u32 bytes, s32 errHandling);
EXPORT_DECL(s32, FSUnmount, void *pClient, void *pCmd, const char *target, s32 errHandling);

EXPORT_DECL(s32, FSGetStat, void *pClient, void *pCmd, const char *path, FSStat *stats, s32 errHandling);
EXPORT_DECL(s32, FSGetStatAsync, void *pClient, void *pCmd, const char *path, void *stats, s32 error, void *asyncParams);
EXPORT_DECL(s32, FSRename, void *pClient, void *pCmd, const char *oldPath, const char *newPath, s32 error);
EXPORT_DECL(s32, FSRenameAsync, void *pClient, void *pCmd, const char *oldPath, const char *newPath, s32 error, void *asyncParams);
EXPORT_DECL(s32, FSRemove, void *pClient, void *pCmd, const char *path, s32 error);
EXPORT_DECL(s32, FSRemoveAsync, void *pClient, void *pCmd, const char *path, s32 error, void *asyncParams);
EXPORT_DECL(s32, FSFlushQuota, void *pClient, void *pCmd, const char* path, s32 error);
EXPORT_DECL(s32, FSFlushQuotaAsync, void *pClient, void *pCmd, const char *path, s32 error, void *asyncParams);
EXPORT_DECL(s32, FSGetFreeSpaceSize, void *pClient, void *pCmd, const char *path, u64 *returnedFreeSize, s32 error);
EXPORT_DECL(s32, FSGetFreeSpaceSizeAsync, void *pClient, void *pCmd, const char *path, u64 *returnedFreeSize, s32 error, void *asyncParams);
EXPORT_DECL(s32, FSRollbackQuota, void *pClient, void *pCmd, const char *path, s32 error);
EXPORT_DECL(s32, FSRollbackQuotaAsync, void *pClient, void *pCmd, const char *path, s32 error, void *asyncParams);

EXPORT_DECL(s32, FSOpenDir, void *pClient, void *pCmd, const char *path, s32 *dh, s32 errHandling);
EXPORT_DECL(s32, FSOpenDirAsync, void *pClient, void* pCmd, const char *path, s32 *handle, s32 error, void *asyncParams);
EXPORT_DECL(s32, FSReadDir, void *pClient, void *pCmd, s32 dh, FSDirEntry *dir_entry, s32 errHandling);
EXPORT_DECL(s32, FSRewindDir, void *pClient, void *pCmd, s32 dh, s32 errHandling);
EXPORT_DECL(s32, FSCloseDir, void *pClient, void *pCmd, s32 dh, s32 errHandling);
EXPORT_DECL(s32, FSChangeDir, void *pClient, void *pCmd, const char *path, s32 errHandling);
EXPORT_DECL(s32, FSChangeDirAsync, void *pClient, void *pCmd, const char *path, s32 error, void *asyncParams);
EXPORT_DECL(s32, FSMakeDir, void *pClient, void *pCmd, const char *path, s32 errHandling);
EXPORT_DECL(s32, FSMakeDirAsync, void *pClient, void *pCmd, const char *path, s32 error, void *asyncParams);

EXPORT_DECL(s32, FSOpenFile, void *pClient, void *pCmd, const char *path, const char *mode, s32 *fd, s32 errHandling);
EXPORT_DECL(s32, FSOpenFileAsync, void *pClient, void *pCmd, const char *path, const char *mode, s32 *handle, s32 error, const void *asyncParams);
EXPORT_DECL(s32, FSReadFile, void *pClient, void *pCmd, void *buffer, s32 size, s32 count, s32 fd, s32 flag, s32 errHandling);
EXPORT_DECL(s32, FSCloseFile, void *pClient, void *pCmd, s32 fd, s32 errHandling);

EXPORT_DECL(s32, FSFlushFile, void *pClient, void *pCmd, s32 fd, s32 error);
EXPORT_DECL(s32, FSTruncateFile, void *pClient, void *pCmd, s32 fd, s32 error);
EXPORT_DECL(s32, FSGetStatFile, void *pClient, void *pCmd, s32 fd, void *buffer, s32 error);
EXPORT_DECL(s32, FSSetPosFile, void *pClient, void *pCmd, s32 fd, u32 pos, s32 error);
EXPORT_DECL(s32, FSWriteFile, void *pClient, void *pCmd, const void *source, s32 block_size, s32 block_count, s32 fd, s32 flag, s32 error);

EXPORT_DECL(s32, FSBindMount, void *pClient, void *pCmd, char *source, char *target, s32 error);
EXPORT_DECL(s32, FSBindUnmount, void *pClient, void *pCmd, char *target, s32 error);

EXPORT_DECL(s32, FSMakeQuota, void *pClient, void *pCmd, const char *path,u32 mode, u64 size, s32 errHandling);
EXPORT_DECL(s32, FSMakeQuotaAsync ,void *pClient, void *pCmd, const char *path,u32 mode, u64 size, s32 errHandling,const void  *asyncParams);

EXPORT_DECL(s32, FSGetCwd,void * client,void * block,char * buffer,u32 bufferSize,u32 flags);

void InitFSFunctionPointers(void) {
    if (coreinitHandle == 0) {
        InitAcquireOS();
    };
    u32* funcPointer = 0;

    OS_FIND_EXPORT(coreinitHandle, FSInit);
    OS_FIND_EXPORT(coreinitHandle, FSShutdown);
    OS_FIND_EXPORT(coreinitHandle, FSAddClient);
    OS_FIND_EXPORT(coreinitHandle, FSAddClientEx);
    OS_FIND_EXPORT(coreinitHandle, FSDelClient);
    OS_FIND_EXPORT(coreinitHandle, FSInitCmdBlock);
    OS_FIND_EXPORT(coreinitHandle, FSGetCurrentCmdBlock);
    OS_FIND_EXPORT(coreinitHandle, FSGetMountSource);

    OS_FIND_EXPORT(coreinitHandle, FSMount);
    OS_FIND_EXPORT(coreinitHandle, FSUnmount);

    OS_FIND_EXPORT(coreinitHandle, FSGetStat);
    OS_FIND_EXPORT(coreinitHandle, FSGetStatAsync);
    OS_FIND_EXPORT(coreinitHandle, FSRename);
    OS_FIND_EXPORT(coreinitHandle, FSRenameAsync);
    OS_FIND_EXPORT(coreinitHandle, FSRemove);
    OS_FIND_EXPORT(coreinitHandle, FSRemoveAsync);
    OS_FIND_EXPORT(coreinitHandle, FSFlushQuota);
    OS_FIND_EXPORT(coreinitHandle, FSFlushQuotaAsync);
    OS_FIND_EXPORT(coreinitHandle, FSGetFreeSpaceSize);
    OS_FIND_EXPORT(coreinitHandle, FSGetFreeSpaceSizeAsync);
    OS_FIND_EXPORT(coreinitHandle, FSRollbackQuota);
    OS_FIND_EXPORT(coreinitHandle, FSRollbackQuotaAsync);

    OS_FIND_EXPORT(coreinitHandle, FSOpenDir);
    OS_FIND_EXPORT(coreinitHandle, FSOpenDirAsync);
    OS_FIND_EXPORT(coreinitHandle, FSReadDir);
    OS_FIND_EXPORT(coreinitHandle, FSRewindDir);
    OS_FIND_EXPORT(coreinitHandle, FSCloseDir);
    OS_FIND_EXPORT(coreinitHandle, FSChangeDir);
    OS_FIND_EXPORT(coreinitHandle, FSChangeDirAsync);
    OS_FIND_EXPORT(coreinitHandle, FSMakeDir);
    OS_FIND_EXPORT(coreinitHandle, FSMakeDirAsync);


    OS_FIND_EXPORT(coreinitHandle, FSOpenFile);
    OS_FIND_EXPORT(coreinitHandle, FSOpenFileAsync);
    OS_FIND_EXPORT(coreinitHandle, FSReadFile);
    OS_FIND_EXPORT(coreinitHandle, FSCloseFile);

    OS_FIND_EXPORT(coreinitHandle, FSFlushFile);
    OS_FIND_EXPORT(coreinitHandle, FSTruncateFile);
    OS_FIND_EXPORT(coreinitHandle, FSGetStatFile);
    OS_FIND_EXPORT(coreinitHandle, FSSetPosFile);
    OS_FIND_EXPORT(coreinitHandle, FSWriteFile);

    OS_FIND_EXPORT(coreinitHandle, FSBindMount);
    OS_FIND_EXPORT(coreinitHandle, FSBindUnmount);

    OS_FIND_EXPORT(coreinitHandle, FSMakeQuota);
    OS_FIND_EXPORT(coreinitHandle, FSMakeQuotaAsync);

    OS_FIND_EXPORT(coreinitHandle, FSGetCwd);
}
