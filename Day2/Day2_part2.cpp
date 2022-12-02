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
    std::unordered_map<char, char> loses_to{{'A', 'Y'}, {'B', 'Z'}, {'C', 'X'}};
    std::unordered_map<char, char> wins_to{{'A', 'Z'}, {'B', 'X'}, {'C', 'Y'}};
    std::unordered_map<char, char> draws_with{{'A', 'X'}, {'B', 'Y'}, {'C', 'Z'}};
    std::unordered_map<char, char> strat{{'X', 'L'}, {'Y', 'D'}, {'Z', 'W'}};
    std::unordered_map<char, int> points{{'X', 1}, {'Y', 2}, {'Z', 3}};

    // calculate total points
    int total_points{0};
    char s;
    char player_choice;
    for(int i{0}; i < player.size(); i++){

        // determine play needed to win lose or draw
        s = strat[player[i]];
        if(s == 'W'){
            total_points += 6;
            player_choice = loses_to[opponent[i]];

        }
        else if(s == 'D'){
            total_points += 3;
            player_choice = draws_with[opponent[i]];
        }
        else{
            player_choice = wins_to[opponent[i]];
        }

        // add points for chosen shape
        total_points += points[player_choice];
    }

    // print result
    std::cout << total_points << std::endl;



    return 0;
}