#ifndef DELAYEXEC_H
#define DELAYEXEC_H

#include <Windows.h>

VOID Wait(_In_ BOOL Large);

VOID SharedUserDataSleep(_In_ SIZE_T Milliseconds);

SIZE_T GetUnixTimestamp();

#endif