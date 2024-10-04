#include <string>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstdint>

bool isOne(char ch) {
    return 'A' <= ch && ch <= 'Z';
}

std::string algorithm(const std::string& IFC_uid) {
    uint64_t mask = 0;
    for (char ch : IFC_uid) {
        mask = (mask << 1) | isOne(ch);
    }

    std::stringstream hex_stream;
    hex_stream << std::uppercase << std::hex << std::setw(22) << std::setfill('0') << mask;
    std::string hex_str = hex_stream.str() + "00";

    std::reverse(hex_str.begin(), hex_str.end());
    return hex_str;
}