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

using namespace std;

#define mp make_pair

// function to check whether position is inside grid
bool valid_grid_pos(const int& row, const int& col, 
const int& n, const int& m){
    return !(row >= n || col >= m || row < 0 || col < 0);
}

int main()
{
    // read in data
    string line;
    vector<string> grid;
    ifstream file("../Day12/day12_data.txt");
    while(getline(file, line)){
        grid.push_back(line);
    }

    // search for the end point
    int n = grid.size();
    int m = grid[0].size();
    pair<int, int> end;
    for(int i{0}; i < n; i++){
        for(int j{0}; j < m; j++){
            if(grid[i][j] == 'E'){
                end = mp(i, j);
                grid[i][j] = 'z'; // end at height z
            }
        }
    }

    queue<pair<int, pair<int, int>>> q;  // queue for bfs
    vector<vector<bool>> visited(n, vector<bool>(m, false));  // tracks if we have visited node

    // start at end node
    q.push(mp(0, end));
    visited[end.first][end.second] = true; 

    // perform bfs
    while(!q.empty()){

        // get distance from start, current row and col of next point in queue
        int dist = q.front().first;
        int row = q.front().second.first;
        int col = q.front().second.second;
        q.pop();  // remove element from queue

        // if we have found start, output distance and quit
        if(grid[row][col] == 'S'){
            cout << dist;
            return 0;
        }

        // can take 4 potential steps in grid
        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        // check all potential children of current pos
        for(int i{0}; i < 4; i++){

            // if child within grid and we haven't visited
            if(valid_grid_pos(row + dx[i], col + dy[i], n, m) 
            && !visited[row + dx[i]][col + dy[i]]){

                // grab child
                // if 'S' then its 'a'
                char child = grid[row+dx[i]][col+dy[i]] == 'S' ? 'a' : grid[row+dx[i]][col+dy[i]];

                // if child is at most one unit higher
                if(grid[row][col] - child <= 1){
                    q.push(mp(dist+1, mp(row+dx[i], col+dy[i])));  // add to queue
                    visited[row+dx[i]][col+dy[i]] = true;  // mark as visited
                }
            }
        }
    }

    cout << "Target not found" << endl;

    return 0;
}