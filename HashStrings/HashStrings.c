#include <Windows.h>
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

const CHAR* StringsToHash[] =
{
	"CreateFiber", "VirtualQuery", "VirtualAlloc", "ConvertThreadToFiber", "SwitchToFiber", "VirtualProtect"
};

const WCHAR* WideStringsToHash[] =
{
	L"Kernel32.dll"
};

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

int main()
{	
	for (DWORD i = 0; i < ARRAY_SIZE(WideStringsToHash); i++)
	{
		printf("%ws hash: 0x%0.8X\n", WideStringsToHash[i], FNV1aW(WideStringsToHash[i]));
	}

	for (DWORD i = 0; i < ARRAY_SIZE(StringsToHash); i++)
	{
		printf("%s hash: 0x%0.8X\n", StringsToHash[i], FNV1a(StringsToHash[i]));
	}
}
