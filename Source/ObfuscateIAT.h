#ifndef OBFUSCATEIAT_H
#define OBFUSCATEIAT_H

#include <Windows.h>

#define KERNEL32DLL  0x4F58D080

ULONG   FNV1aW(_In_ LPCWSTR String);

ULONG   FNV1a(_In_ LPCSTR String);

HMODULE GetDllHandle(_In_ ULONG DllNameHash);

FARPROC GetFunctionAddress(_In_ HMODULE ModuleHandle, _In_ ULONG FunctionNameHash);

#endif