#include <Windows.h>
#include "DelayExec.h"

BOOL Execute(LPFIBER_START_ROUTINE FiberStartAddress)
{
	LPVOID FiberAddress = NULL;

	if (!(FiberAddress = CreateFiber(0x00, FiberStartAddress, NULL)))
	{
		return FALSE;
	}

	Wait(TRUE);

	if (ConvertThreadToFiber(NULL))
	{
		return FALSE;
	}

	SwitchToFiber(FiberAddress);
}