#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <iostream>

inline bool isOne(char ch) {
    return 'A' <= ch && ch <= 'Z';
}

void algorithm(const char* IFC_uid, char* hex_result) {
    long long int mask = 0;
    for (size_t i = 0; i < 22; ++i) {
        mask = (mask << 1) | isOne(IFC_uid[i]);
    }
    char const table[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    int i = 8;
    *(long long int*)hex_result = 0x3030303030303030;
    while (mask) {
        hex_result[--i] = table[mask & 0b1111];
        mask >>= 4;
    };
}

// int main() {
//     const char* IFC_uid = "7AkhabfbJvr_$6J0GVGk9M";
//     char result[9];
//     algorithm(IFC_uid, result);
//     std::cout << result << std::endl;
//     // 00120CC1
//     //0023a101
// }