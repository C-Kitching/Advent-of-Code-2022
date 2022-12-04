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

using namespace std;

int main()
{
    // decalre variables
    string line;
    vector<pair<pair<int, int>, pair<int, int>>> elf_pairs;
    pair<int, int> elf1, elf2;
    pair<pair<int, int>, pair<int, int>> elf_pair;
    char c;
    int elf1_start, elf1_end, elf2_start, elf2_end;
    int count{0};

    // read in data
    string file_path{"../Day4/day4_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while (std::getline(my_file, line)) {
            stringstream ss(line);
            ss >> elf1_start >> c >> elf1_end >> c >> elf2_start >> c >> elf2_end;

            // first elf
            elf1.first = elf1_start;
            elf1.second = elf1_end;

            // second elf
            elf2.first = elf2_start;
            elf2.second = elf2_end;

            // elf pair
            elf_pair.first = elf1;
            elf_pair.second = elf2;

            // store elf pair
            elf_pairs.push_back(elf_pair);
        }
    }

    // check all pairs
    for(auto (&elf_pair) : elf_pairs){

        // extract elf pairs
        elf1 = elf_pair.first;
        elf2 = elf_pair.second;

        // count number of searches containing other search
        if((elf2.first <= elf1.second && elf2.second >= elf1.second) ||
        (elf1.first <= elf2.second && elf1.second >= elf2.second)){
            count++;
        }
    }

    cout << count << endl;

    return 0;
}