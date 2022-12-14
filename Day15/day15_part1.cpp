#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

#define mp make_pair

// class to store sensor beacon pair information
class sensor_beacon_pair
{
    public:
        int sensor_row;
        int sensor_col;
        int beacon_row;
        int beacon_col;
        int taxi_dist;

        int calc_taxi_dist(){
            return abs(sensor_col - beacon_col) + abs(sensor_row - beacon_row);
        }
};

// function to parse string and split into tokens
void parse(const string &txt, vector<string> (&strs))
{
    stringstream ss(txt);
    string token;
    strs.clear();
    while(ss >> token) strs.push_back(token);
}


// read data and return cave structure
vector<sensor_beacon_pair> read_data(const string& file)
{
    vector<sensor_beacon_pair> ret;

    ifstream fs(file);
    string line;

    // read each line of data and build sensor beacon objects
    while(getline(fs, line)){
        vector<string> s;
        sensor_beacon_pair sbp;

        parse(line,s);
        sbp.sensor_col = stoi(s[2].substr(2, s[2].length() - 3));
        sbp.sensor_row = stoi(s[3].substr(2, s[3].length() - 3));
        sbp.beacon_col = stoi(s[8].substr(2, s[8].length() - 3));
        sbp.beacon_row = stoi(s[9].substr(2, s[9].length() - 2));
        sbp.taxi_dist = sbp.calc_taxi_dist();

        ret.push_back(sbp);
    }

    return ret;
}

int main()
{
    // read in data
    vector<sensor_beacon_pair> pairs;
    pairs = read_data("../Day15/day15_data.txt");

    // define target
    int Y = 2000000;

    // build ranges
    vector<pair<int, int>> ranges;
    for(auto& s : pairs){
        int side = s.taxi_dist - abs(s.sensor_row - Y);
        if(side < 0) continue;
        ranges.emplace_back(s.sensor_col - side, s.sensor_col + side);
    }
    sort(ranges.begin(), ranges.end());

    // group ranges
    int r{0};
    for(int i{0}; i < (int)ranges.size(); i++){
        if(ranges[r].second >= ranges[i].first){
            ranges[r].second = max(ranges[r].second, ranges[i].second);
        }
        else{
            r++;
            ranges[r] = ranges[i];
        }
    }

    // sum all ranges
    int res{0};
    for(int i{0}; i <= r; i++) res += ranges[i].second - ranges[i].first + 1;
    cout << res - 1 << endl;  // one beacon at target 

    return 0;
}