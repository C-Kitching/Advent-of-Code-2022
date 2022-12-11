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
    string temp_s;
    int temp_n;
    char temp_c;
    vector<vector<int>> monkeys_items;
    vector<int> monkeys_operations;
    vector<int> monkeys_test;
    vector<pair<int, int>> monkeys_to_throw_to;

    // read in data
    string file_path{"../Day10/day10_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while(getline(my_file, line)) {
            stringstream ss(line);

            ss >> temp_s;
            if(temp_s == "Monkey"){
                ss >> temp_n;
                current_monkey = temp_n;
            }




        }  
    }
    return 0;
}