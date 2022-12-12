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
    std::string file_path{"/home_th/kitching/Documents/Advent of Code 2022/Day 1/Day1_data.txt"};
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

    // calculate total calroies
    std::vector<int> total_calories;
    for(auto (&elf): data){
        int calories = std::accumulate(elf.begin(), elf.end(), 0);
        total_calories.push_back(calories);
    }

    // sort calories
    std::sort(total_calories.begin(), total_calories.end());

    // calculate total from top 3
    int top_3_calories{total_calories.end()[-1] + total_calories.end()[-2] + total_calories.end()[-3]};

    // print result
    std::cout << top_3_calories << std::endl;

    return 0;
}