#include "algo_c-string.cc"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>



int main() {

    std::ifstream file("../test/test_data.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }

    
    std::string IFC_line;
    size_t count = 0;
    auto start = std::chrono::high_resolution_clock::now();
    while (std::getline(file, IFC_line)) {
        count ++;
        const char* IFC_uid = IFC_line.c_str();
        char result[9];
        algorithm(IFC_uid, result);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = end - start;

    file.close();

    std::ofstream time_file("time.txt");
            if (!time_file.is_open()) {
                std::cerr << "Failed to open errors.txt for writing" << std::endl;
                return 1;
            }
    time_file << "Iterations: " << count<< '\n';
    time_file << "duration: " << duration.count() / 1000000000.0 << "s\n";
    //000000000
    time_file << "time per string: " << duration.count() / count << "ns" << std::endl;
    time_file.close();
    }