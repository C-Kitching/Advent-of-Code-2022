#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include <bitset>

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
const int STEPS = 26;
int total_rate;
string all_opened = "";
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

// function to compare two string
bool cmp(pair<string, int> &a, pair<string, int> &b)
{
    return a.second > b.second;
}

// recursive dp function
// 'opened' is a bitstring with n_useful bits
// bit i is 1 if the ith useful valve is opened, and 0 otherwise
void find_max_pressure(int time, int pos, string opened, int dist[60][60])
{
    // compute solution to this subproblem
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
                // if we cannot, then we will have the same amount of pressure
                // at the end of the 26 minutes.
                // update the value for this combination of valves opened accordingly
                if (memory[STEPS - 1].count(opened) != 1)
                {
                    memory[STEPS - 1][opened] = 0;
                }
                memory[STEPS - 1][opened] = max(memory[STEPS - 1][opened], memory[time][opened]);
            }
            // if we can open it without exceeding the time limit, ...
            else
            {
                // compute total pressure released by opening that valve next
                valve next_valve = valves[next_id];
                int released_pressure = (STEPS - next_time) * next_valve.rate;

                // update the bitstring since this valve is now open
                string *next_opened = new string(opened);
                (*next_opened)[next] = '1';

                // update memo table with the pressure released at the given time
                // with this combination of valves opened
                int next_pressure = released_pressure + memory[time][opened];
                if (memory[next_time].count(*next_opened) != 1)
                {
                    memory[next_time][*next_opened] = 0;
                }
                memory[next_time][*next_opened] = max(memory[next_time][*next_opened], next_pressure);

                // recursively fill in memo table
                find_max_pressure(next_time, next_id, *next_opened, dist);
            }
        }
    }
}

int main()
{
    // read data
    read_input("C:/Users/Christopher/OneDrive/Desktop/GitHub/Advent-of-Code-2022/Day16/day16_test.txt");

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
    for(int x{0}; x < n_useful; x++){
        init += "0";
        all_opened += "1";
    }

    /*
    idea: the user and the elephant take independent paths.
    to be optimal, the user and the elephant should not open the same valves,
    i.e. the valves opened by the user and the elephant have no overlaps.
    hence, we look at the combinations of valves opened at time 26 and their
    corresponding amount of pressure released.
    we want to find two such combinations such that there are no overlaps in the
    valves opened between both combinations, and their sum of pressure released
    is maximum.
    */

    // find max pressure
    memory[0][init] = 0;
    find_max_pressure(0, valve_ids["AA"], init, dist);

    vector<pair<string, int>> last;
    for (auto z : memory[STEPS - 1])
    {
        last.push_back(z);
    }
    sort(last.begin(), last.end(), cmp);

    // compute sums of non-intersecting valve-opening patterns
    // as a heuristic, limit to the top 15 patterns
    int max_sum = 0;
    for (int n = 0; n < 15; n++)
    {
        int cur_sum = last[n].second;
        bitset<16> first_bits(last[n].first);
        for (int m = n + 1; m < last.size(); m++)
        {
            bitset<16> second_bits(last[m].first);
            // if the bitwise AND of both patterns are 0, there are
            // no valves that are opened in both patterns
            if ((first_bits & second_bits) == 0)
            {
                cur_sum += last[m].second;
                max_sum = max(max_sum, cur_sum);
                break;
            }
        }
    }

    cout << max_sum << endl;

    return 0;
}