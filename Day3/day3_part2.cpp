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
    std::vector<std::vector<std::string>> groups;
    if (my_file.is_open()) {
        std::vector<std::string> group;
        int counter{0};
        while (std::getline(my_file, line)) {
            group.push_back(line);
            counter++;
            if(counter == 3){
                groups.push_back(group);
                group.clear();
                counter = 0;
            }
        }
    }

    // loop through groups
    int score{0};
    for(auto& group : groups){

        // check each char of first string
        for(char& c : group[0]){

            // if char in other two strings
            if(group[1].find(c) != std::string::npos && group[2].find(c) != std::string::npos){
                if(std::islower(c)) score += c - 'a' + 1;
                else score += std::tolower(c) - 'a' + 27;
                break;
            }
        }
    }

    std::cout << score << std::endl;


    return 0;
}