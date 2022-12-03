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
    std::string file_path{"../Day3/day3_data.txt"};
    std::ifstream my_file(file_path);
    std::string line;
    std::vector<std::string> backpack{"vJrwpWtwJgWrhcsFMMfFFhFp",
    "jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
    "PmmdzqPrVvPwwTWBwg",
    "wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
    "ttgJtRGJQctTZtZT",
    "CrZsJsPPZsGzwwsLwLmpwMDw",};
    if (my_file.is_open()) {
        while (std::getline(my_file, line)) {
            backpack.push_back(line);
        }
    }

    // extract all items
    std::string first_part, second_part;
    int N;
    int score{0};
    for(std::string& item : backpack){

        // split string
        N = item.size();
        first_part = item.substr(0, N/2);
        second_part = item.substr(N/2, N);

        // loop through first string and attempt to find occurences in second
        for(char& c : first_part){
            if(second_part.find(c) != std::string::npos){
                if(std::islower(c)) score += c - 'a' + 1;
                else score += c - 'c' + 27;
                break;
            }
        }
    }

    std::cout << score << std::endl;


    return 0;
}