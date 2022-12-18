#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <sstream>
#include <unordered_map>
#include <map>
#include <regex>
#include <bitset>

using namespace std;

struct valve
{
    int rate;
    vector<string> tunnels;
};

void find_max_pressure(int time, int pos, string opened, int dist[60][60]);

// it's okay to use global variables for competitive programming, right?
// ... right?
int n_valves;
int n_useful;
const int STEPS = 26;
map<string, int> memo[STEPS];
map<string, int> valve_ids;
vector<valve> valves;
vector<int> useful_valve_ids;
int dist[60][60] = {0}; // hard-coded to be 60x60

bool cmp(pair<string, int> &a, pair<string, int> &b)
{
    return a.second > b.second;
}

int main()
{
    string line;

    // regex stuff
    regex num("[0-9]+");
    regex name("[A-Z]{2}");
    regex_token_iterator<string::iterator> rend;

    // parse input
    int valve_id = 0;
    while (!cin.eof())
    {
        getline(cin, line);
        valve *cur_valve = new valve();

        // parse valve rate
        regex_token_iterator<string::iterator> num_match(line.begin(), line.end(), num);
        cur_valve->rate = stoi(*num_match);

        // parse valve name
        regex_token_iterator<string::iterator> name_match(line.begin(), line.end(), name);
        string valve_name = *name_match++;

        // parse tunnels to other vaults
        vector<string> *tunnels = new vector<string>();
        while (name_match != rend)
        {
            tunnels->push_back(*name_match++);
        }
        cur_valve->tunnels = *tunnels;

        // store the current valve
        valve_ids[valve_name] = valve_id;
        valves.push_back(*cur_valve);

        // call the current valve "useful" if it has a positive rate
        if (cur_valve->rate > 0)
        {
            useful_valve_ids.push_back(valve_id);
        }

        valve_id += 1;
    }

    // set constants
    n_valves = valve_id;
    n_useful = useful_valve_ids.size();

    // init distance array with a large value,
    // and set initial distances between adjacent valves to 1
    for (int row = 0; row < n_valves; row++)
    {
        for (int col = 0; col < n_valves; col++)
        {
            dist[row][col] = n_valves + 100;
        }
        for (string vname : valves[row].tunnels)
        {
            int vid = valve_ids[vname];
            dist[row][vid] = 1;
            dist[vid][row] = 1;
        }
    }

    // use Floyd-Warshall to find all-pairs shortest path between all valves
    for (int k = 0; k < n_valves; k++)
    {
        for (int i = 0; i < n_valves; i++)
        {
            for (int j = 0; j < n_valves; j++)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // get zero bitstring corresponding to # useful vaults
    string init = "";
    for (int x = 0; x < n_useful; x++)
    {
        init += "0";
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
    memo[0][init] = 0;
    find_max_pressure(0, valve_ids["AA"], init, dist);

    vector<pair<string, int>> last;
    for (auto z : memo[STEPS - 1])
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
}

// recursive bottom-up DP function
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
                if (memo[STEPS - 1].count(opened) != 1)
                {
                    memo[STEPS - 1][opened] = 0;
                }
                memo[STEPS - 1][opened] = max(memo[STEPS - 1][opened], memo[time][opened]);
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
                int next_pressure = released_pressure + memo[time][opened];
                if (memo[next_time].count(*next_opened) != 1)
                {
                    memo[next_time][*next_opened] = 0;
                }
                memo[next_time][*next_opened] = max(memo[next_time][*next_opened], next_pressure);

                // recursively fill in memo table
                find_max_pressure(next_time, next_id, *next_opened, dist);
            }
        }
    }
}