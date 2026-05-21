#pragma once
#include <cstdint>
#ifdef RSA_DLL_EXPORTS
#define RSA_API __declspec(dllexport)
#else
#define RSA_API __declspec(dllimport)
#endif
extern "C"
{
    RSA_API void GenerateKeys(
        uint64_t p,
        uint64_t q,
        uint64_t& e,
        uint64_t& d,
        uint64_t& n
    );
    RSA_API uint64_t Encrypt(
        uint64_t message,
        uint64_t e,
        uint64_t n
    );
    RSA_API uint64_t Decrypt(
        uint64_t encryptedMessage,
        uint64_t d,
        uint64_t n
    );
}