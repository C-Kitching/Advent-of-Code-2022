#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <random>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <utility>
#include <chrono>
#include <deque>

using namespace std;

void update_piece_pos(const pair<int, int> (&H_coord), 
    pair<int, int> (&T_coord))
{
    // if in same column but H two steps further
    // move T one step in H direction
    if(H_coord.first == T_coord.first){
        if(H_coord.second-T_coord.second >= 2){
            T_coord.second++;
        }
        else if(T_coord.second-H_coord.second >= 2){
            T_coord.second--;
        }
    }

    // if in same row but H tow steps further
    // move T one step in H direction
    else if(H_coord.second == T_coord.second){
        if(H_coord.first-T_coord.first >= 2){
            T_coord.first++;
        }
        else if(T_coord.first-H_coord.first >= 2){
            T_coord.first--;
        }
    }

    // if H not in same row or column and not touching
    // move T diagonally one step towards H
    else if(abs(H_coord.first - T_coord.first) > 1 
    || abs(H_coord.second - T_coord.second) > 1){

        // right and up
        if(H_coord.first > T_coord.first 
        && H_coord.second > T_coord.second){
            T_coord.first++;
            T_coord.second++;
        }

        // right and down
        else if(H_coord.first > T_coord.first 
        && H_coord.second < T_coord.second){
            T_coord.first++;
            T_coord.second--;
        }

        // left and down
        else if(H_coord.first < T_coord.first 
        && H_coord.second < T_coord.second){
            T_coord.first--;
            T_coord.second--;
        }

        // left and up
        else if(H_coord.first < T_coord.first 
        && H_coord.second > T_coord.second){
            T_coord.first--;
            T_coord.second++;
        }
    }
}

int main()
{
    // decalre variables
    string buffer;
    string line;
    int size;
    char dir;
    vector<pair<char, int>> steps;
    set<pair<int, int>> visited;

    // read in data
    string file_path{"../Day9/day9_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while(getline(my_file, line)) {
            stringstream ss(line);
            ss >> dir >> size;
            pair<char, int> step(dir, size);
            steps.push_back(step);
        }  
    }

    // initally all at start
    vector<pair<int, int>> coords;
    for(int i{0}; i<=9; i++) coords.push_back(pair<int, int> (0,0));

    // execute all steps
    for(auto& step : steps){

        dir = step.first;
        for(int i{0}; i < step.second; i++){

            // move the head
            if(dir == 'U') coords[0].second++;
            else if(dir == 'D') coords[0].second--;
            else if(dir == 'L') coords[0].first--;
            else coords[0].first++;

            // move the remaining 9 pieces
            for(int i{1}; i < coords.size(); i++){

                // use the previous piece as the head
                pair<int, int> head = coords[i-1];

                // update the position of the current piece
                update_piece_pos(head, coords[i]);
            }

            // add tail position to record
            visited.insert(coords.back());
        }
    }

    // calculate total unique coords visited by tail
    int unique_coords = visited.size();

    // output results
    cout << unique_coords << endl;

    return 0;
}