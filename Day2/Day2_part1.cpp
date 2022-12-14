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

    // create maps
    std::unordered_map<char, char> gets_beat_by{{'A', 'Y'}, {'B', 'Z'}, {'C', 'X'}};
    std::unordered_map<char, char> draws_with{{'A', 'X'}, {'B', 'Y'}, {'C', 'Z'}};
    std::unordered_map<char, int> points{{'X', 1}, {'Y', 2}, {'Z', 3}};

    // calculate total points
    int total_points{0};
    for(int i{0}; i < player.size(); i++){

        // add score for shape we selected
        total_points += points[player[i]];

        // add points for result
        if(gets_beat_by[opponent[i]] == player[i]) total_points += 6;
        else if(draws_with[opponent[i]] == player[i]) total_points += 3;
    }

    // print result
    std::cout << total_points << std::endl;



    return 0;
}