#include <iostream>
#include <windows.h>
#include <cstdint>
#include <io.h>
#include <fcntl.h>

using namespace std;
typedef void (*pGenerateKeys)(
    uint64_t p,
    uint64_t q,
    uint64_t& e,
    uint64_t& d,
    uint64_t& n
    );
typedef uint64_t(*pEncrypt)(
    uint64_t message,
    uint64_t e,
    uint64_t n
    );
typedef uint64_t(*pDecrypt)(
    uint64_t encryptedMessage,
    uint64_t d,
    uint64_t n
    );
int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    HMODULE hDll = LoadLibrary(L"RSA_DLL.dll");
    if (hDll == NULL)
    {
        wcout << L"Error: RSA_DLL.dll was not loaded" << endl;
        return 1;
    }
    wcout << L"RSA_DLL.dll loaded successfully" << endl;
    pGenerateKeys GenerateKeys =
        (pGenerateKeys)GetProcAddress(hDll, "GenerateKeys");
    pEncrypt Encrypt =
        (pEncrypt)GetProcAddress(hDll, "Encrypt");
    pDecrypt Decrypt =
        (pDecrypt)GetProcAddress(hDll, "Decrypt");
    if (GenerateKeys == NULL || Encrypt == NULL || Decrypt == NULL)
    {
        wcout << L"Error: function address was not found" << endl;
        FreeLibrary(hDll);
        return 1;
    }
    wcout << L"Function addresses received successfully" << endl;
    wcout << endl;
    uint64_t e0, d0, n0;
    uint64_t e1, d1, n1;
    GenerateKeys(10007ULL, 10009ULL, e0, d0, n0);
    GenerateKeys(10037ULL, 10039ULL, e1, d1, n1);
    uint64_t testData[] =
    {
        12345ULL,
        54321ULL,
        100000ULL,
        250000ULL,
        500000ULL
    };
    wcout << L"Keys of user 0:" << endl;
    wcout << L"e0 = " << e0 << L", d0 = " << d0 << L", n0 = " << n0 << endl;
    wcout << endl;
    wcout << L"Keys of user 1:" << endl;
    wcout << L"e1 = " << e1 << L", d1 = " << d1 << L", n1 = " << n1 << endl;
    wcout << endl;
    for (int i = 0; i < 5; i++)
    {
        uint64_t t = testData[i];
        uint64_t e1t = Encrypt(t, e1, n1);
        uint64_t d1e1t = Decrypt(e1t, d1, n1);
        uint64_t e0d1e1t = Encrypt(d1e1t, e0, n0);
        uint64_t d0e0d1e1t = Decrypt(e0d1e1t, d0, n0);
        wcout << L"Test " << i + 1 << endl;
        wcout << L"Initial value: " << t << endl;
        wcout << L"e1t = " << e1t << endl;
        wcout << L"d1e1t = " << d1e1t << endl;
        wcout << L"e0d1e1t = " << e0d1e1t << endl;
        wcout << L"d0e0d1e1t = " << d0e0d1e1t << endl;
        if (d1e1t == t && d0e0d1e1t == t)
        {
            wcout << L"Result: correct" << endl;
        }
        else
        {
            wcout << L"Result: error" << endl;
        }
        wcout << L"------------------------" << endl;
    }
    wcout << endl;
    wcout << L"Select language:" << endl;
    wcout << L"1 - Ukrainian" << endl;
    wcout << L"2 - English" << endl;
    wcout << L"Your choice: ";
    int choice;
    wcin >> choice;
    HMODULE hLang = NULL;
    if (choice == 1)
    {
        hLang = LoadLibrary(L"LangUA.dll");
    }
    else
    {
        hLang = LoadLibrary(L"LangEN.dll");
    }
    if (hLang == NULL)
    {
        wcout << L"Error: language DLL was not loaded" << endl;
        FreeLibrary(hDll);
        return 1;
    }
    wchar_t buffer[256];
    wcout << endl;
    wcout << L"Information from resource DLL:" << endl;
    LoadString(hLang, 101, buffer, 256);
    wcout << L"Surname: " << buffer << endl;
    LoadString(hLang, 102, buffer, 256);
    wcout << L"Faculty: " << buffer << endl;
    LoadString(hLang, 103, buffer, 256);
    wcout << L"Group: " << buffer << endl;
    LoadString(hLang, 104, buffer, 256);
    wcout << L"Subject: " << buffer << endl;
    FreeLibrary(hLang);
    FreeLibrary(hDll);

    return 0;
}