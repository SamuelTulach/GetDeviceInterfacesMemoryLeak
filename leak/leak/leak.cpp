#include <Windows.h>
#include <winnt.h>
#include <winternl.h>
#include <iostream>
#include "ntdll.h"

bool running = true;

DWORD WINAPI SpamThread(PVOID number)
{
    printf("Thread %i started\n", (int)number);
    
    while (running)
    {
        GUID dummyGuid = { 0 };
        UNICODE_STRING variableName = RTL_CONSTANT_STRING(L"dummyVariable");

        char buffer[8];

        ntdll::NtSetSystemEnvironmentValueEx(&variableName, &dummyGuid, buffer, sizeof(buffer), ATTRIBUTES);
    }

    return 0;
}

int main()
{
    printf("Setting SE_SYSTEM_ENVIRONMENT_PRIVILEGE privilegie...\n");
    bool enabled = false;
    const NTSTATUS status = ntdll::RtlAdjustPrivilege(22L, true, false, reinterpret_cast<PBOOLEAN>(&enabled));
    if (!NT_SUCCESS(status))
    {
        printf("Failed to set SE_SYSTEM_ENVIRONMENT_PRIVILEGE privilegie!\n");
        return -1;
    }

    printf("Starting threads...\n");
    for (int i = 0; i < 8; i++)
    {
        CreateThread(nullptr, NULL, SpamThread, (PVOID)i, NULL, nullptr);
    }

    getchar();
    running = false;

    return 0;
}
