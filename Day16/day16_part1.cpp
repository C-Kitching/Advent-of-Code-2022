#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>
#include <unordered_map>

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
unordered_map<string, int> memory[STEPS];  // memory for dp problem
unordered_map<string, int> valve_ids;
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
int find_max_pressure(int time, int curr_valve_name, string opened, const int dist[60][60])
{
    if(opened == "111111"){
        int max_pressure = 
    }

    // if solution to subproblem previously computed
    // dont need to do it again
    if(memory[time].count(opened) == 1) return memory[time][opened];

    // otherwise, compute solution to this subproblem
    else{
        int max_pressure{0};

        // iterate over all useful valves to see where to move
        for(int next_valve_id{0}; next_valve_id < n_useful; next_valve_id++){

            // skip opened valves
            if(opened[next_valve_id] == '1') continue;

            // check all unopened useful vavles
            else{

                // check if we can open valve without exceeding time limit
                // time to open is current time + travel time + opening time
                int next_valve_name = useful_valve_ids[next_valve_id];
                int next_time = time + dist[curr_valve_name][next_valve_name] + 1;
                if(next_time >= STEPS) continue;

                // if we can open without exceeding time limit
                else{

                    // compute total pressure released by opening that valve next
                    valve next_valve = valves[next_valve_name];
                    int next_pressure = (STEPS - next_time) * next_valve.rate;

                    // update bitstring since next valve now open
                    string *next_opened = new string(opened);
                    (*next_opened)[next_valve_id] = '1';

                    // recursively compute max pressure
                    max_pressure = max(max_pressure, next_pressure 
                        + find_max_pressure(next_time, next_valve_name, *next_opened, dist));
                }
            }
        }

        // memorise result and return
        memory[time][opened] = max_pressure;
        return max_pressure;
    }

}

int main()
{
    // read data
    read_input("../Day16/day16_test.txt");

    // initalise dist array with large value
    // set initial distance between adjacent valves to 1
    for(int r{0}; r < n_valves; r++){
        for(int c{0}; c < n_valves; c++){
            dist[r][c] = n_valves + 100;
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
    for(int x{0}; x < n_useful; x++) init += "0";

    // find max pressure
    int max_pressure = find_max_pressure(0, valve_ids["AA"], init, dist);
    cout << max_pressure << endl;

    return 0;
}