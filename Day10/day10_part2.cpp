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
    string instruction;
    int cycle{0};
    int r{0};
    vector<int> sprite_pos{0, 1, 2};

    // set up CRT
    vector<vector<char>> CRT;
    for(int i{0}; i < 6; i++){
        vector<char> row(40, '.');
        CRT.push_back(row);
    }

    // read in data
    string file_path{"../Day10/day10_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while(getline(my_file, line)) {
            stringstream ss(line);
            ss >> instruction;
            if(instruction == "noop"){
                auto it = find(sprite_pos.begin(), sprite_pos.end(), cycle);
                if(it != sprite_pos.end()){
                    CRT[r][cycle] = '#'; 
                }
                cycle++;
                if(cycle == 40){
                    r++;
                    cycle %= 40;
                }
            }
            else{
                ss >> size;

                // draw hash
                auto it = find(sprite_pos.begin(), sprite_pos.end(), cycle);
                if(it != sprite_pos.end()){
                    CRT[r][cycle] = '#'; 
                }
                cycle++;
                if(cycle == 40){
                    r++;
                    cycle %= 40;
                }
                it = find(sprite_pos.begin(), sprite_pos.end(), cycle);
                if(it != sprite_pos.end()){
                    CRT[r][cycle] = '#'; 
                }
                cycle++;
                if(cycle == 40){
                    r++;
                    cycle %= 40;
                }

                // update sprite pos
                for(auto& e : sprite_pos){
                    e = (e+size)%40;
                }
            }
        }  
    }

    // output results
    for(auto& r : CRT){
        for(auto& c : r){
            cout << c;
        }
        cout << "\n";
    }

    return 0;
}