#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

#define mp make_pair
#define ll long long

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

    // check all heights
    for(int Y{3214125}; Y <= 4000000; Y++){

        cout << Y << endl;

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

        // if there is more than one range, there is a gap
        if(r > 0){
            ll X = ranges[0].second + 1;
            cout << X*4000000 + Y << endl;
            return 0;
        }
    }
}