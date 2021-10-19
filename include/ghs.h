#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Calls each static init function from the funcptr list "_ctors[]"
void __call_ctors(void); //! DO NOT CALL

// Destructs all static objects
void __call_dtors(void); //! DO NOT CALL

void __gh_float_printf(void);
void __gh_long_long_printf(void*, int, int, int);

void __gh_set_errno(int);

void __ghs_flock_file(void);
void __ghs_funlock_file(void);
void* __ghs_flock_ptr(void);

void __PPCEXIT(signed int status);
void _Exit(int status);

// Replaces pure virtual functions in vtable entries. Causes the game to hang by default.
//* Hacked in Tsuru to have different functionality (see /debug/exceptions.cpp)
void __pure_virtual_called(void);

// Replaces deleted virtual functions in vtable entries (usually). Causes the game to hang by default.
//* Hacked in Tsuru to have different functionality (see /debug/exceptions.cpp)
void __deleted_virtual_called(void);

// Clears memory at ptr
// @param ptr Pointer to memory to be cleared
// @param size Size of area to clear [size_t]
void __memzero(void* ptr, unsigned int size);

// GHS implementation of strlen
// Get string length
// @param str String to be evaluated
// @return Length of the input string
int __ghs_strlen(const char* str);

// GHS implementation of strcmp
// Compare if two strings are equal
// @param str1 The first string to compare
// @param str2 The second string to compare
// @return < 0 if str1 is less than str2;
//           0 if str1 is identical to str2;
//         > 0 if str1 is greater than str2
int __ghs_strcmp(const char* str1, const char* str2);

// Allocates and initializes mutex
// @param mutex Pointer to target mutex
void __ghs_mtx_init(void* mutex);

// Frees memory for mutex
// @param mutex Pointer to target mutex
void __ghs_mtx_dst(void* mutex);

// Locks mutex
// @param mutex Pointer to target mutex
void __ghs_mtx_lock(void* mutex);

// Unlocks mutex
// @param mutex Pointer to target mutex
void __ghs_mtx_unlock(void* mutex);

void __ghsLock(void);
void __ghsUnlock(void);

void __gh_memclr32(void*, int);
void __gh_memclr32(void);

// Initializes and allocates an array
// @param output Pointer to memory to allocate to
// @param entryCount Number of entries in the array
// @param entrySize Size of each array entry
// @param entryCtor Pointer to entry constructor
void __vec_new(void* output, unsigned int entryCount, unsigned int entrySize, void (*entryCtor)());

// Destructs and frees an array
// @param input Pointer to array in memory
// @param entryCount Number of entries in the array
// @param entrySize Size of each array entry
// @param entryDtor Pointer to entry destructor
void __vec_delete(void* input, unsigned int entryCount, unsigned int entrySize, void (*entryDtor)(), int, int);

// Called when a static object has been constructed to register a destruction that must be done at program termination
// @param ptr Pointer to needed destruction entry that is to be added to the front of a list of needed destructions that this routine keeps
void __record_needed_destruction(void* ptr);

#ifdef __cplusplus
}
#endif
