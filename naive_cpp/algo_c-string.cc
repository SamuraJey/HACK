
#include <stddef.h>

inline bool isOne(char ch) {
    return 'A' <= ch && ch <= 'Z';
}
//__attribute__((noinline))
void algorithm(const char* IFC_uid, char* hex_result) {
    long long int mask = 0;
    for (size_t i = 0; i < 22; ++i) {
        mask = (mask << 1) | isOne(IFC_uid[i]);
    }
    static char const table[] = "0123456789ABCDEF";
    int i = 8;
    *(long long int*)hex_result = 0x3030303030303030ULL;  // = "00000000"
    do {
        hex_result[--i] = table[mask & 0b1111];
    } while (mask >>= 4);
}