#ifndef OBFUSCATEIAT_H
#define OBFUSCATEIAT_H

#include <Windows.h>

#define KERNEL32DLL_HASH		  0x4F58D080

#define VIRTUALQUERY_HASH		  0xDA272FDB
#define VIRTUALALLOC_HASH		  0xF46EEE66
#define VIRTUALPROTECT_HASH   0x13F429EC

#define CREATEFIBER_HASH		      0xF7FD131C
#define CONVERTTHREADTOFIBER_HASH 0x7CA22442
#define SWITCHTOFIBER_HASH        0xFF63E97F

ULONG   FNV1aW(_In_ LPCWSTR String);

ULONG   FNV1a(_In_ LPCSTR String);

HMODULE GetDllHandle(_In_ ULONG DllNameHash);

FARPROC GetFunctionAddress(_In_ HMODULE ModuleHandle, _In_ ULONG FunctionNameHash);

#endif
