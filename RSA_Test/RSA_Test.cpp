#include <iostream>
#include "../RSA_DLL/RSA.h"

using namespace std;
int main()
{
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
    cout << "Keys of user 0:" << endl;
    cout << "e0 = " << e0 << ", d0 = " << d0 << ", n0 = " << n0 << endl;
    cout << endl;
    cout << "Keys of user 1:" << endl;
    cout << "e1 = " << e1 << ", d1 = " << d1 << ", n1 = " << n1 << endl;
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        uint64_t t = testData[i];
        uint64_t e1t = Encrypt(t, e1, n1);
        uint64_t d1e1t = Decrypt(e1t, d1, n1);
        uint64_t e0d1e1t = Encrypt(d1e1t, e0, n0);
        uint64_t d0e0d1e1t = Decrypt(e0d1e1t, d0, n0);
        cout << "Test " << i + 1 << endl;
        cout << "Initial value: " << t << endl;
        cout << "e1t = " << e1t << endl;
        cout << "d1e1t = " << d1e1t << endl;
        cout << "e0d1e1t = " << e0d1e1t << endl;
        cout << "d0e0d1e1t = " << d0e0d1e1t << endl;
        if (d1e1t == t && d0e0d1e1t == t)
        {
            cout << "Result: correct" << endl;
        }
        else
        {
            cout << "Result: error" << endl;
        }
        cout << "------------------------" << endl;
    }
    return 0;
}