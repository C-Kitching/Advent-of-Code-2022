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
    string file_path{"../Day9/day9_sam.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while(getline(my_file, line)) {
            stringstream ss(line);
            ss >> dir >> size;
            pair<char, int> step(dir, size);
            steps.push_back(step);
        }  
    }

    // initally both at start
    pair<int, int> H_coord(0, 0);
    pair<int, int> T_coord(0, 0);

    // execute all steps
    for(auto& step : steps){

        dir = step.first;
        for(int i{0}; i < step.second; i++){

            // move the head
            if(dir == 'U') H_coord.second++;
            else if(dir == 'D') H_coord.second--;
            else if(dir == 'L') H_coord.first--;
            else H_coord.first++;

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

            // add tails position to record
            visited.insert(T_coord);
        }
    }

    // calculate total unique coords visited by tail
    int unique_coords = visited.size();

    // output results
    cout << unique_coords << endl;

    return 0;
}