#include <Windows.h>

#define		PAGE_SIZE					4096
#define		SET_TO_MULTIPLE_OF_4096(X)	( ((X) + 4095) & (~4095) )

BOOL Inject(_In_ PBYTE PayloadBuffer, _In_ SIZE_T PayloadSize, _Out_ PBYTE* AllocationStart)
{
	DWORD NewSize		 = SET_TO_MULTIPLE_OF_4096(PayloadSize);
	PVOID StartAddress   = NULL;

	// Reserve enough memory
	if (!VirtualAlloc(NULL, &StartAddress, &NewSize, MEM_RESERVE, PAGE_READONLY))
	{
		return FALSE;
	}

	// Start committing with RW
	PVOID TempAddress = StartAddress;

	for (DWORD i = 0; i < NewSize / PAGE_SIZE; i++)
	{
		if (!VirtualAlloc(NULL, &TempAddress, PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE))
		{
			return FALSE;
		}
		TempAddress = (PVOID)((ULONG_PTR)StartAddress + PAGE_SIZE);
	}

	// Change to RWX

	TempAddress         = StartAddress;
	DWORD OldProtection = NULL;

	for (DWORD i = 0; i < NewSize / PAGE_SIZE; i++)
	{
		if (!VirtualProtect(&TempAddress, PAGE_SIZE, PAGE_EXECUTE_READWRITE, &OldProtection))
		{
			return FALSE;
		}
		TempAddress = (PVOID)((ULONG_PTR)StartAddress + PAGE_SIZE);
	}


	return TRUE;
}