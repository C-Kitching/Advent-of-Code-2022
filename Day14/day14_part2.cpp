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
#include <queue>
#include <numeric>

using namespace std;

#define mp make_pair

// parse string input and return vector of rock coords
vector<pair<int, int>> parse(const string& input, int& min_y)
{
    int i{0};
    vector<pair<int, int>> ret;

    while(i < input.length()){

        // read coords
        int a = 0, b = 0;
        while(i < input.length() && isdigit(input[i])){
            a *= 10;
            a += input[i++] - '0';
        }
        i++;
        while(i < input.length() && isdigit(input[i])){
            b *= 10;
            b += input[i++] - '0';
        }

        ret.push_back(mp(b, a));  // store as pair

        // check for minimum
        min_y = max(min_y, b); 

        // skip non-numbers
        while(i < input.length() && !isdigit(input[i])) i++;
    }

    return ret;
}

// build cave structure
void build_cave(vector<vector<int>> (&cave), 
    const vector<pair<int, int>> rock_line)
{
    for(int i{1}; i < rock_line.size(); i++){

        // draw horizontal rock line
        if(rock_line[i-1].first == rock_line[i].first){
            for(int j = min(rock_line[i-1].second, rock_line[i].second); j <= max(rock_line[i-1].second, rock_line[i].second); j++)
                cave[rock_line[i].first][j] = 1;
        }

        // draw vertical rock line
        else if(rock_line[i-1].second == rock_line[i].second){
            for(int j = min(rock_line[i-1].first, rock_line[i].first); j <= max(rock_line[i-1].first, rock_line[i].first); j++)
                cave[j][rock_line[i].second] = 1;
        }
    }
}

// read data and return cave structure
vector<vector<int>> read_data(const string& file)
{
    ifstream fs(file);
    string line;
    string token;
    vector<vector<int>> cave(1000, vector<int>(1000, 0));
    int min_y = 0;

    // build cave system
    while(getline(fs, line)){
        vector<pair<int, int>> rock_line = parse(line, min_y);
        build_cave(cave, rock_line);
    }

    // add floor to cave
    int floor_height = min_y + 2;
    for(int i{0}; i < 1000; i++) cave[floor_height][i] = 1;

    return cave;
}

// simulate each grain of falling sand
bool simulate_sand(vector<vector<int>> (&cave), 
    deque<pair<int, int>> (&pos_history))
{
    // start at the previous position of the last grain
    pair<int, int> sand_pos = pos_history.back();
    pos_history.pop_back();

    while(true){
        // down
        if(cave[sand_pos.first+1][sand_pos.second] == 0){
            pos_history.push_back(sand_pos);
            sand_pos.first++;

            // fallen to abyss
            if(sand_pos.first >= 999) return true;
        }
        // down-left
        else if(cave[sand_pos.first+1][sand_pos.second-1] == 0){
            pos_history.push_back(sand_pos);
            sand_pos.first++;
            sand_pos.second--;
        }
        // down-right
        else if(cave[sand_pos.first+1][sand_pos.second+1] == 0){
            pos_history.push_back(sand_pos);
            sand_pos.first++;
            sand_pos.second++;
        }
        // came to rest
        else{
            cave[sand_pos.first][sand_pos.second] = 2;

            // check if blocking exit 
            if(sand_pos == pos_history.front()) return true;
            
            return false;
        }
    }
}

int main()
{
    // read in data
    vector<vector<int>> cave = read_data("../Day14/day14_test.txt");

    // count number of stationary sand grains
    int sand_grains{0};
    deque<pair<int, int>> sand_history;
    sand_history.push_back(mp(0, 500));
    while(true){
        sand_grains++;
        if(simulate_sand(cave, sand_history)){
            cout << sand_grains << endl;
            return 0;
        }
    }

    return 0;
}