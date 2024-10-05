#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <fstream>

inline bool isOne(char ch) {
    return 'A' <= ch && ch <= 'Z';
}

__attribute__((noinline))
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
    }
    hex_result[8] = '\0'; // Null-terminate the result
}

// int main() {
//     std::ios::sync_with_stdio(false);
//     std::ifstream file("../test/test_data_2gb.txt");
//     if (!file.is_open()) {
//         std::cerr << "Failed to open file" << std::endl;
//         return 1;
//     }
//     std::ofstream file2 ("../test/test_answers_22gb.txt.tmp");
//     if (!file2.is_open()) {
//         std::cerr << "Failed to open file" << std::endl;
//         return 1;
//     }

//     std::string IFC_line;
//     while (std::getline(file, IFC_line)) {
//         const char* IFC_uid = IFC_line.c_str();
//         char result[9];
//         algorithm(IFC_uid, result);
//         file2 << result << std::endl;
//     }

// }