SHA-256 Cryptographic Hashing Header
​File: src/crypto/sha256.h
​
​Defines the interface for the SHA-256 hashing algorithm, which is the core
​Proof-of-Work function for ORPHAN BLOCK Bitcoin.
​(Based on Bitcoin's reference implementation structure)
​#pragma once
​#include <stdint.h>
#include <stddef.h>
​// Standard size for a SHA-256 hash output
static const size_t SHA256_SIZE = 32;
​// The structure that holds the internal state of the SHA-256 process
class CSHA256 {
private:
uint32_t s[8];
unsigned char buf[64];
size_t bytes;
​public:
// Initializes the internal state of the hash calculation
void Init();
