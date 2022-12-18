#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>
#include <map>

using namespace std;

// defines
#define mp make_pair

// structure to define valve
struct valve
{
    int rate;
    vector<string> neighbours;
};

// globals
int n_valves{0};
int n_useful;
const int STEPS = 30;
int total_rate;
string all_opened = "";
map<string, int> memo[STEPS];  // memory for dp problem
map<string, int> valve_ids;
vector<valve> valves;
vector<int> useful_valve_ids;
int dist[60][60] = {0};  // distances between valves (increase 60 if more valves)

// function to read data
void read_input(const string& file)
{

    // read each line of file
    ifstream fs(file);
    string line;
    while(getline(fs, line)){

        // read each word
        int idx{0};
        stringstream ss(line);
        string word;
        valve v;
        while(getline(ss, word, ' ')){

            // valve name
            if(idx == 1){
                valve_ids[word] = n_valves;
            }

            // valve rate 
            else if(idx == 4){
                v.rate = stoi(word.substr(5, word.size() - 1));
                total_rate += v.rate;

                // if useful
                if(v.rate > 0) useful_valve_ids.push_back(n_valves);
            }

            // valve connections
            else if(idx >= 9){
                if(word[word.size()-1] == ','){
                    word = word.substr(0, word.size() - 1);
                }
                v.neighbours.push_back(word);
            }

            idx++;  // next token
        }
        valves.push_back(v);
        n_valves++;  // next valve
    }
    n_useful = useful_valve_ids.size();
}

// recursive dp function
// 'opened' is a bitstring with n_useful bits
// bit i is 1 if the ith useful valve is opened, and 0 otherwise
int find_max_pressure(int time, int pos, string opened, int dist[60][60])
{

    // check if solution to this subproblem has been previously computed
    if (memo[time].count(opened) == 1)
    {
        return memo[time][opened];
    }
    else if (opened == all_opened)
    {
        return 0;
    }
    // otherwise, compute solution to this subproblem
    else
    {
        int max_pressure = 0;
        // iterate over all useful valves
        for (int next = 0; next < n_useful; next++)
        {
            // skip valves that are already open
            if (opened[next] == '1')
            {
                continue;
            }
            // for every unopened useful valve, ...
            else
            {
                // check if we can open it without exceeding the time limit
                int next_id = useful_valve_ids[next];
                int next_time = time + dist[pos][next_id] + 1;
                if (next_time >= STEPS)
                {
                    continue;
                }
                // if we can open it without exceeding the time limit, ...
                else
                {
                    // compute total pressure released by opening that valve next
                    valve next_valve = valves[next_id];
                    int next_pressure = (STEPS - next_time) * next_valve.rate;

                    // update the bitstring since this valve is now open
                    string *next_opened = new string(opened);
                    (*next_opened)[next] = '1';

                    // recursively compute max pressure
                    max_pressure = max(max_pressure, next_pressure + find_max_pressure(next_time, next_id, *next_opened, dist));
                }
            }
        }
        // memoize result and return
        if (memo[time].count(opened) != 1)
        {
            memo[time][opened] = 0;
        }
        memo[time][opened] = max_pressure;
        return max_pressure;
    }
}

int main()
{
    // read data
    read_input("C:/Users/Christopher/OneDrive/Desktop/GitHub/Advent-of-Code-2022/Day16/day16_data.txt");

    // initalise dist array with large value
    // set initial distance between adjacent valves to 1
    for(int r{0}; r < n_valves; r++){
        for(int c{0}; c < n_valves; c++){
            dist[r][c] = n_valves + 1000;
        }
        for(string& valve_name : valves[r].neighbours){
            int valve_id = valve_ids[valve_name];
            dist[r][valve_id] = 1;
            dist[valve_id][r] = 1;
        }
    }

    // Floyd-Warshall to find all-pairs shortest path between all valves
    for(int k{0}; k < n_valves; k++){
        for(int i{0}; i < n_valves; i++){
            for(int j{0}; j < n_valves; j++){
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // get zero bitstring corresponding to number of useful valves
    string init = "";
    for(int x{0}; x < n_useful; x++){
        init += "0";
        all_opened += "1";
    }

    // find max pressure
    int max_pressure = find_max_pressure(0, valve_ids["AA"], init, dist);
    cout << max_pressure << endl;

    return 0;
}