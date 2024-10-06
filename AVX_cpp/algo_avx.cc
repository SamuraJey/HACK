
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
    uint32_t BitMask = _mm256_movemask_epi8(ByteMask);
    /*
    __m128i v = _mm_cvtsi32_si128(BitMask);
    __m128i hi = _mm_slli_epi64(v, 32 - 4);  // input_num >> 4 in the 2nd dword
    // This trick to avoid a shuffle only works for 32-bit integers
#ifdef __AVX512VL__
                                             // UNTESTED, TODO: check this constant
    v = _mm_ternarylogic_epi32(v, hi, _mm_set1_epi8(0x0f), 0b10'10'10'00);  // IDK why compilers don't do this for us
#else
    v = _mm_or_si128(v, hi);                    // the overlaping 4 bits will be masked away anyway, don't need _mm_blend_epi32
    v = _mm_and_si128(v, _mm_set1_epi8(0x0f));  // isolate the nibbles because vpermb isn't available
#endif
    __m128i nibble_interleave = _mm_setr_epi8(7, 3, 6, 2, 5, 1, 4, 0,
                                              0, 0, 0, 0, 0, 0, 0, 0);
    v = _mm_shuffle_epi8(v, nibble_interleave);  // and put them in order into the low qword
    __m128i hex_lut = _mm_setr_epi8('0', '1', '2', '3', '4', '5', '6', '7',
                                    '8', '9', 'a', 'b', 'c', 'd', 'e', 'f');
    v = _mm_shuffle_epi8(hex_lut, v);

    _mm_storel_epi64((__m128i*)hex_result, v);  // movq 8 ASCII hex digits (u32)
*/

    // curesed int to hex string converion.
    // IFC strings -1-> int mask -2-> Hex string
    // x86 uses litle endian thus conversion 1 screw things up.
    // Mask order is correct, same as IFC char.
    // But as a number it is byte reversed from L_endian stand point.
    // So regular Hex conversion aloriths do not work.
    // Ususaly it won't be a problem. A conviniants, actualy.
    // But i cant realy figure out AVX converiosn my self.
    // Found no solution from Web for Big endian AVX, lol.
    static char const table[] = "0123456789ABCDEF";
    *(uint64_t*)hex_result = 0x3030303030303030ULL;  // = "00000000"
    hex_result[2] = table[BitMask & 0b11];
    hex_result[3] = table[(BitMask >>= 2) & 0b1111];
    hex_result[4] = table[(BitMask >>= 4) & 0b1111];
    hex_result[5] = table[(BitMask >>= 4) & 0b1111];
    hex_result[6] = table[(BitMask >>= 4) & 0b1111];
    hex_result[7] = table[BitMask & 0b1111];
}