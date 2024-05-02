#include <Windows.h>

#include "Structures.h"
#include "ObfuscateIAT.h"


ULONG FNV1aW(_In_ LPCWSTR String)
{
	ULONG Hash = 0x6A6CCC06;

	while (*String)
	{
		Hash ^= (UCHAR)*String++;
		Hash *= 0x25EDE3FB;
	}

	return Hash;
}

ULONG FNV1a(_In_ LPCSTR String)
{
	ULONG Hash = 0x6A6CCC06;

	while (*String)
	{
		Hash ^= (UCHAR)*String++;
		Hash *= 0x25EDE3FB;
	}

	return Hash;
}

PPEB GetPEBAddress() 
{
	_asm {  xor    rax,rax
		mov    rdx,rax
		add    dl,0x69
		sub    rdx,0x9
		mov    rax,QWORD PTR gs:[rax+rdx*1]
		ret  
	     }
}


HMODULE GetDllHandle(_In_ ULONG DllNameHash)
{
	PLIST_ENTRY Head   = (PLIST_ENTRY) & ((PPEB)GetPEBAddress)->LoaderData->InMemoryOrderModuleList;
	PLIST_ENTRY Next   = Head->Flink;
	PLDR_MODULE Module = (PLDR_MODULE)((PBYTE)Next - 0x10);

	while (Next != Head)
	{
		Module = (PLDR_MODULE)((PBYTE)Next - 0x10);

		if (Module->BaseDllName.Buffer != NULL)
		{
			if (DllNameHash - FNV1aW(Module->BaseDllName.Buffer) == 0) 
			{
				return (HMODULE)Module->BaseAddress;
			}
		}
		Next = Next->Flink;
	}
	return NULL;
}

FARPROC GetFunctionAddress(_In_ HMODULE DllHandle, _In_ ULONG FunctionNameHash) 
{
	if (DllHandle == NULL)
	{
		return NULL;
	}

	PIMAGE_NT_HEADERS       NTHeaders             = (PIMAGE_NT_HEADERS)((PBYTE)DllHandle + ((PIMAGE_DOS_HEADER)(PBYTE)DllHandle)->e_lfanew);
	PIMAGE_EXPORT_DIRECTORY ExportDirectory       = (PIMAGE_EXPORT_DIRECTORY)((PBYTE)DllHandle + NTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
	DWORD                   ExportDirectorySize   = NTHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

	PDWORD		        FunctionNameArray     = (PDWORD)((PBYTE)DllHandle + ExportDirectory->AddressOfNames);
	PDWORD			FunctionAddressArray  = (PDWORD)((PBYTE)DllHandle + ExportDirectory->AddressOfFunctions);
	PWORD			AddressOfNameOrdinals = (PWORD)((PBYTE)DllHandle  + ExportDirectory->AddressOfNameOrdinals);

	for (DWORD i = 0; i < ExportDirectory->NumberOfFunctions; i++) 
	{
		LPCSTR FunctionName      = (LPCSTR)(FunctionNameArray[i]);
		PVOID  FunctionAddress   = (PVOID)(FunctionAddressArray[AddressOfNameOrdinals[i]]);

		if (FunctionNameHash - FNV1a(FunctionName) == 0)
		{
			return (FARPROC)FunctionAddress;
		}
	}
	return NULL;
}
