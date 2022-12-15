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
            return abs(sensor_col - beacon_col)*abs(sensor_row - beacon_row);
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
        sbp.sensor_row = stoi(s[2].substr(2, s[2].length() - 3));
        sbp.sensor_col = stoi(s[3].substr(2, s[3].length() - 3));
        sbp.beacon_row = stoi(s[8].substr(2, s[8].length() - 3));
        sbp.beacon_col = stoi(s[9].substr(2, s[9].length() - 2));
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

    // test data
    int min_col = -4;
    int max_col = 26;
    int r = 10;

    // actual data
    r = 2000000; 
    min_col = -1077481;
    max_col = 4401794;

    int n = 0;
    for (int c = min_col; c <= max_col; c++) {

        // assume position is valid
        bool valid_pos = true;

        for(sensor_beacon_pair sbp : pairs) {

            // calculate distance from point to sensor
            int dist = abs(sbp.sensor_col - c) + abs(sbp.sensor_row - r);

            // if point closer to sensor than its closest beacon,
            // the beacon cannot be there
            if(dist <= sbp.calc_taxi_dist()) {

                // position no longer valid
                valid_pos = false;

                // check for a sensor or beacon at that point
                for(auto& sb : pairs) {
                    if((sb.beacon_col == c && sb.beacon_row == r) || 
                    (sb.sensor_col == c && sb.sensor_row == r)){

                        // found a sensor or beacon so reduce valid pos by 1
                        // dont need to keep searching
                        valid_pos = true;
                        break;
                    }
                }
            }
        }

        if(!valid_pos) n++;

        cerr << r << "," << c << " " << n << endl;
    }
    cout << n << endl;


    return 0;
}