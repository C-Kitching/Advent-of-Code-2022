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
    marker = buffer.substr(0, 4);

    // count frequency of characters
    unordered_map<char, int> count;
    for(auto& c : marker) count[c]++;

    // search all other markers for target marker
    int N = buffer.size();
    for(int i{1}; i < N-3; i++){

        // extract new marker 
        marker = buffer.substr(i, 4);

        // update freq counts
        count[*buffer.substr(i-1,1).c_str()]--;
        count[*buffer.substr(i+3,1).c_str()]++;

        // count number of unique elements
        int c{0};
        for(auto& p : count){
            if(p.second == 1) c++;
        }

        // if target, print and break
        if(c == 4){
            cout << marker << endl;
            cout << i+4;
            break;
        }
    }

    return 0;
}