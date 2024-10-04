#include "algo_c-string.cc"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>



int main() {

    std::ifstream file("../test/test_data.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }
    std::ifstream file2 ("../test/test_answers.txt");
    if (!file2.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }


    std::string IFC_line;
    std::string Hex;
    std::vector<std::pair<const char*, char*>> errors;
    while (std::getline(file, IFC_line)) {
        std::getline(file2, Hex);
        const char* IFC_uid = IFC_line.c_str();
        const char* Hex_c_str = Hex.c_str();
        char result[9];
        algorithm(IFC_uid, result);
        if (std::strcmp(result, Hex_c_str) != 0) {
            std::cout << "Mismatch: " << result << " != " << Hex_c_str << std::endl;
            errors.push_back(std::make_pair(Hex_c_str, result));
        }
    }

    file.close();
    file2.close();

    std::ofstream error_file("errors.txt");
            if (!error_file.is_open()) {
                std::cerr << "Failed to open errors.txt for writing" << std::endl;
                return 1;
            }

    if(errors.size()==0){
        error_file << "Corect" << std::endl;
        std::cout << "IF" << std::endl;
    }else{
        std::cout << "ELSE" << std::endl;
        for (const auto& error : errors) {
            error_file << "Expected: " << error.first << ", Got: " << error.second << '\n';
        }
    }
    error_file.close();
    }