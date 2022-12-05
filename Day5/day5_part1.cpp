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
#include <deque>

using namespace std;

int main()
{
    // decalre variables
    string line;
    vector<deque<char>> stack;
    vector<int> num_to_move;
    vector<int> start_pos;
    vector<int> end_pos;
    string temp_s;
    int temp_i;

    // build inital setup
    stack.push_back({'Z', 'T', 'F', 'R', 'W', 'J', 'G'});
    stack.push_back({'G', 'W', 'M'});
    stack.push_back({'J', 'N', 'H', 'G'});
    stack.push_back({'J', 'R', 'C', 'N', 'W'});
    stack.push_back({'W', 'F', 'S', 'B', 'G', 'Q', 'V', 'M'});
    stack.push_back({'S', 'R', 'T', 'D', 'V', 'W', 'C'});
    stack.push_back({'H', 'B', 'N', 'C', 'D', 'Z', 'G', 'V'});
    stack.push_back({'S', 'J', 'N', 'M', 'G', 'C'});
    stack.push_back({'G', 'P', 'N', 'W', 'C', 'J', 'D', 'L'});

    // read in data
    string file_path{"../Day5/day5_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while (std::getline(my_file, line)) {
            stringstream ss(line);
            ss >> temp_s >> temp_i;
            num_to_move.push_back(temp_i);
            ss >> temp_s >> temp_i;
            start_pos.push_back(temp_i);
            ss >> temp_s >> temp_i;
            end_pos.push_back(temp_i);
        }
    }

    // move boxes around
    for(int i{0}; i < num_to_move.size(); i++){

        // remove boxes from first stack
        deque<char> to_move;
        int start = start_pos[i];
        int end = end_pos[i];
        for(int j{0}; j < num_to_move[i]; j++){
            char box = stack[start-1].back();
            stack[start-1].pop_back();
            to_move.push_back(box);
        }

        // store boxes on new stack
        for(auto& box : to_move) stack[end-1].push_back(box);
    }

    // print out result
    for(auto& pile : stack) cout << pile.back();

    return 0;
}