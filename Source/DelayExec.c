#include <Windows.h>

SIZE_T GetUnixTimestamp()
{
    const SIZE_T TICKS_PER_MILLISECOND = 10000;

    LARGE_INTEGER Time =
    {
        .LowPart = *(DWORD*)(0x7FFE0000 + 0x14),
        .HighPart = *(LONG*)(0x7FFE0000 + 0x1c)
    };

    return (SIZE_T)(Time.QuadPart / TICKS_PER_MILLISECOND);
}

VOID SharedUserDataSleep(_In_ SIZE_T Milliseconds)
{
    SIZE_T End = GetUnixTimestamp() + Milliseconds;

    for (DWORD i = 0x00; GetUnixTimestamp() < End; i++)
    {

    }

    if ((GetUnixTimestamp() - End) > 5000)
    {
        return;
    }
}

VOID Wait(_In_ BOOL Large)
{
    volatile SIZE_T x = 0;

#pragma warning( disable : 6387)
    if (!Large)
    {
        x = SetCriticalSectionSpinCount(NULL, NULL);
        SharedUserDataSleep(2000);

        x = GetWindowContextHelpId(NULL);
        SharedUserDataSleep(2000);

        x = GetWindowLongPtrW(NULL, NULL);
        SharedUserDataSleep(1000);
    }
    else 
    {
        x = RegisterClassW(NULL);

        x = GetLastError();
        SharedUserDataSleep(3000);

        x = IsWindowVisible(NULL);

        x = ConvertDefaultLocale(NULL);
        SharedUserDataSleep(2000);

        x = MultiByteToWideChar(NULL, NULL, NULL, NULL, NULL, NULL);

        x = IsDialogMessageW(NULL, NULL);
        SharedUserDataSleep(2000);
    }
#pragma warning( pop )
}