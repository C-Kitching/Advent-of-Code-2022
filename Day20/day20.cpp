#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>

using namespace std;

#define mp make_pair

vector<int> read_data(const string& file_name){
    ifstream fs(file_name);
    string line;
    vector<int> ret;
    while(getline(fs, line)) ret.push_back(stoi(line));
    return ret; 
}

void mix(const vector<int> (&data), deque<pair<int, int>> (&position_list)){

    for(int i{0}; i < data.size(); i++){
        int curr_idx = position_list.at(mp(data[i], i));
    }





}

int main()
{
    vector<int> data = read_data("../Day20/day20_test.txt");
    deque<pair<int, int>> position_list;
    for(int i{0}; i < data.size(); i++){
        position_list.push_back(mp(data[i], i));
    }


    return 0;
}