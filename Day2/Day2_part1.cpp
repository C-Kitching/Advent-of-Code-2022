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
    std::string file_path{"../Day2/Day2_data.txt"};
    std::ifstream my_file(file_path);
    std::string line;
    std::vector<char> opponent, player;
    if (my_file.is_open()) {
        char o, p;
        while (std::getline(my_file, line)) {
            std::stringstream ss(line);
            ss >> o >> p;
            opponent.push_back(o);
            player.push_back(p);
        }
    }

    int x{5};



    return 0;
}