#ifndef INJECT_H
#define INJECT_H

#include <Windows.h>

BOOL Inject(_In_ PBYTE PayloadBuffer, _In_ SIZE_T PayloadSize, _Out_ PBYTE* AllocationStart);

#endif