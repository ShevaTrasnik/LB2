// dllmain.cpp : Визначає точку входу для DLL.
#include "pch.h"
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cstdint>

using namespace std;
uint32_t CalculateChecksum(const vector<char>& data)
{
    uint32_t sum = 0;
    for (char byte : data)
    {
        sum += static_cast<unsigned char>(byte);
    }
    return sum;
}
bool CheckDllIntegrity(HMODULE hModule)
{
    char fileName[MAX_PATH];
    if (GetModuleFileNameA(hModule, fileName, MAX_PATH) == 0)
    {
        return false;
    }
    ifstream input(fileName, ios::binary);
    if (!input.is_open())
    {
        return false;
    }
    vector<char> data(
        (istreambuf_iterator<char>(input)),
        istreambuf_iterator<char>()
    );
    input.close();
    if (data.size() < sizeof(uint32_t))
    {
        return false;
    }
    uint32_t savedChecksum = 0;
    memcpy(
        &savedChecksum,
        &data[data.size() - sizeof(uint32_t)],
        sizeof(uint32_t)
    );
    data.resize(data.size() - sizeof(uint32_t));
    uint32_t currentChecksum = CalculateChecksum(data);
    return savedChecksum == currentChecksum;
}
BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved
)
{
    char message[256];
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        sprintf_s(
            message,
            "DLL_PROCESS_ATTACH\nlpReserved = %p",
            lpReserved
        );
        MessageBoxA(
            NULL,
            message,
            "RSA_DLL DllMain",
            MB_OK
        );
        if (!CheckDllIntegrity(hModule))
        {
            MessageBoxA(
                NULL,
                "DLL integrity check failed!",
                "Integrity error",
                MB_OK | MB_ICONERROR
            );

            return FALSE;
        }
        MessageBoxA(
            NULL,
            "DLL integrity check successful!",
            "Integrity check",
            MB_OK
        );
        break;
    }
    case DLL_PROCESS_DETACH:
        sprintf_s(
            message,
            "DLL_PROCESS_DETACH\nlpReserved = %p",
            lpReserved
        );
        MessageBoxA(
            NULL,
            message,
            "RSA_DLL DllMain",
            MB_OK
        );
        break;

    case DLL_THREAD_ATTACH:
        break;

    case DLL_THREAD_DETACH:
        break;
    }
    return TRUE;
}