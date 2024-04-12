#ifndef INJECT_H
#define INJECT_H

#include <Windows.h>

PVOID Inject(_In_ PBYTE PayloadBuffer, _In_ SIZE_T PayloadSize);
VOID _Memcpy(_In_ PVOID Destination, _In_ PVOID Source, _In_ SIZE_T Length);

#endif