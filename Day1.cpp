#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <utility>
#include <chrono>

int main()
{
    // read in data
    std::string file_path{"/home_th/kitching/Documents/Advent of Code 2022/Day1_data.txt"};
    std::ifstream my_file(file_path);
    std::string line;
    std::vector<std::vector<double>> data;
    std::vector<double> elf;
    if (my_file.is_open()) {
        while (std::getline(my_file, line)) {
            if(line.empty()){
                data.push_back(elf);
                elf.clear();
            } else elf.push_back(std::stoi(line));
        }
    }



    return 0;
}