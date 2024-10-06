
#include <immintrin.h>
#include <stddef.h>

#include <cstdint>

//__attribute__((noinline))
void algorithm(const char* IFC_uid, char* hex_result) {
    static __m256i const A_mask = _mm256_set1_epi8('@');
    static __m256i const Z_mask = _mm256_set1_epi8('[');

    __m256i IFC_avx = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(IFC_uid));
    __m256i ByteMask1 = _mm256_cmpgt_epi8(IFC_avx, A_mask);
    __m256i ByteMask2 = _mm256_cmpgt_epi8(Z_mask, IFC_avx);
    __m256i ByteMask = _mm256_and_si256(ByteMask1, ByteMask2);
    uint32_t BitMask = _mm256_movemask_epi8(ByteMask);  // arithmetic ordering. Not sequantial

    // curesed int to hex string converion.
    // IFC strings -1-> Byte mask -2-> int mask -2-> Hex string
    // 1) strings stored common ordering: first Byte contain first char.
    // load operant interpret string as a number.
    // x86 uses litle endian: firs Byte is smallest Byte (bit ordering is direct).
    // as a result first char is stored as smallest Byte in AVX reg.
    // 2) compress Byte mask to bit mask with arithmetic ordering in mind
    // first cahr = smalest Byte = smallest bit. so arithmeticaly we get nice reversed bit sequence.
    // But remember the endian. Memory wise all Bytes of result u32 are reversed with respect to arithmetic notation.
    // Resulting in common Byte ordering and reversed bit ordoring.
    // More over we need to arithmeticaly pad Int mask with leading zeros.
    // It is important to pad at bit mask level becouse 22 is not devisable by 4.
    // first non zero Hex value need only 2 bits of mask and all folowing full 4.
    // with regular iteratin we'll convert to hex bits shifted by 2
    // I cant realy figure out AVX converiosn my self.
    // Found no solution from Web for this bizare conversion.
    static char const table[] = "084C2A6E195D3B7F";  // cursed table
    *(uint64_t*)hex_result = 0x3030303030303030ULL;  // = "00000000"
    hex_result[2] = table[BitMask << 2 & 0b1100];
    hex_result[3] = table[(BitMask >>= 2) & 0b1111];
    hex_result[4] = table[(BitMask >>= 4) & 0b1111];
    hex_result[5] = table[(BitMask >>= 4) & 0b1111];
    hex_result[6] = table[(BitMask >>= 4) & 0b1111];
    hex_result[7] = table[(BitMask >>= 4) & 0b1111];
}