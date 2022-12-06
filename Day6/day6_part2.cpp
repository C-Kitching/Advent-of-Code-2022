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
    string buffer;
    string line;
    int size_of_target{14};

    // read in data
    string file_path{"../Day6/day6_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while (std::getline(my_file, line)) {
            buffer = line;
        }   
    }

    // get initial marker
    string marker;
    marker = buffer.substr(0, size_of_target);

    // count frequency of characters
    unordered_map<char, int> count;
    for(auto& c : marker) count[c]++;

    // search all other markers for target marker
    int N = buffer.size();
    for(int i{1}; i < N-(size_of_target-1); i++){

        // extract new marker 
        marker = buffer.substr(i, size_of_target);

        // update freq counts
        count[*buffer.substr(i-1,1).c_str()]--;
        count[*buffer.substr(i+(size_of_target-1),1).c_str()]++;

        // count number of unique elements
        int c{0};
        for(auto& p : count){
            if(p.second == 1) c++;
        }

        // if target, print and break
        if(c == size_of_target){
            cout << marker << endl;
            cout << i+size_of_target;
            break;
        }
    }

    return 0;
}