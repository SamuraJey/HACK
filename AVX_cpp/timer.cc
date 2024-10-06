#include <chrono>
#include <fstream>
#include <iostream>

#include "algo_avx.cc"

int main() {
    std::ifstream file_len("../test/test_data.txt", std::ios::binary | std::ios::ate);  // Open file and seek to end
    if (!file_len.is_open()) {
        throw std::runtime_error("Failed to open file");
    }
    size_t len = file_len.tellg();
    file_len.close();
    std::ifstream file("../test/test_data.txt", std::ios::in | std::ios::binary);
    char* buffer = new char[len];
    file.read(buffer, len);
    file.close();

    char const* IFC_uid = buffer;
    char const* buffer_end = buffer + len;
    char result[9];
    char const* it = buffer;
    while (it < buffer + 25) {
        std::cout << (int)*it << '\n';
        it += 1;
    }
    if (it >= buffer_end) {
        std::cout << "no new lines\n";
    } else {
        std::cout << reinterpret_cast<uintptr_t>(it) - reinterpret_cast<uintptr_t>(buffer) << '\n';
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (; IFC_uid < buffer_end; IFC_uid += 24) {
        algorithm(IFC_uid, result);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;

    std::ofstream time_file("time.txt");
    if (!time_file.is_open()) {
        std::cerr << "Failed to open errors.txt for writing" << std::endl;
        return 1;
    }
    time_file << "Iterations: " << (len / 24) << '\n';
    time_file << "duration: " << duration.count() / 1000000000.0 << "s\n";
    // 000000000
    time_file << "time per string: " << duration.count() / (len / 24.) << "ns" << std::endl;
    time_file << "calls per second: " << (len / 24.) * 1000.0 / duration.count() << " milions" << std::endl;
    time_file.close();
    std::cout << "done" << std::endl;
}