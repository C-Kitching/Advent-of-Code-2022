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

void check_for_target(int& cycle, const int& X, int& total_signal_strength, 
    const unordered_set<int> (&target_cycles))
{
    if(target_cycles.find(cycle) != target_cycles.end()){
        int signal_strength = cycle*X;
        total_signal_strength += signal_strength;
    }
}

int main()
{
    // decalre variables
    string buffer;
    string line;
    int size;
    string instruction;
    int cycle{0};
    int X{1};
    unordered_set<int> target_cycles{20, 60, 100, 140, 180, 220};
    int total_signal_strength{0};
    int signal_strength;

    // read in data
    string file_path{"../Day10/day10_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while(getline(my_file, line)) {
            stringstream ss(line);
            ss >> instruction;
            if(instruction == "noop"){
                cycle++;
                check_for_target(
                    cycle, X, total_signal_strength, target_cycles);
            }
            else{
                ss >> size;

                cycle++;
                check_for_target(
                    cycle, X, total_signal_strength, target_cycles);
                cycle++;
                check_for_target(
                    cycle, X, total_signal_strength, target_cycles);

                X += size;
            }
        }  
    }

    // output results
    cout << total_signal_strength << endl;

    return 0;
}