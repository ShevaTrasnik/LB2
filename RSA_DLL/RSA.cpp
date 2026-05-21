#include "pch.h"
#include "RSA.h"
static uint64_t GCD(uint64_t a, uint64_t b)
{
    while (b != 0)
    {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
static uint64_t ModPow(uint64_t base, uint64_t exponent, uint64_t mod)
{
    uint64_t result = 1;
    base = base % mod;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
        {
            result = (result * base) % mod;
        }

        base = (base * base) % mod;
        exponent = exponent / 2;
    }
    return result;
}
static uint64_t FindD(uint64_t e, uint64_t phi)
{
    uint64_t d = 1;
    while ((d * e) % phi != 1)
    {
        d++;
    }
    return d;
}
void GenerateKeys(uint64_t p, uint64_t q, uint64_t& e, uint64_t& d, uint64_t& n)
{
    n = p * q;
    uint64_t phi = (p - 1) * (q - 1);
    e = 3;
    while (GCD(e, phi) != 1)
    {
        e += 2;
    }
    d = FindD(e, phi);
}
uint64_t Encrypt(uint64_t message, uint64_t e, uint64_t n)
{
    return ModPow(message, e, n);
}
uint64_t Decrypt(uint64_t encryptedMessage, uint64_t d, uint64_t n)
{
    return ModPow(encryptedMessage, d, n);
}