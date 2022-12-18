#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <unordered_map>

using namespace std;

#define mp make_pair

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

map<pair<pair<int, int>, int>, bool> read_data(const string& file)
{
    ifstream fs(file);
    string line;
    int x, y, z;
    char c;
    map<pair<pair<int, int>, int>, bool> obsideans;
    while(getline(fs, line)){
        stringstream ss(line);
        ss >> x >> c >> y >> c >> z;
        obsideans[mp(mp(x, y), z)] = true;
    }

    return obsideans;
}


int main()
{
    // read in data
    // map with true is block at that position
    map<pair<pair<int, int>, int>, bool> obsideans = read_data("../Day18/day18_data.txt");
    map<pair<pair<int, int>, int>, bool> obsideans_copy = obsideans;

    // determine positions of water and steam
    map<pair<pair<int, int>, int>, bool> water;
    queue<pair<pair<int, int>, int>> q;
    q.push(mp(mp(-1, -1), -1));
    while(!q.empty()){
        pair<pair<int, int>, int> tmp = q.front();
        water[tmp] = true;
        q.pop();

        for(int i{0}; i < 6; i++){
            int next_x = tmp.first.first + dx[i];
            int next_y = tmp.first.second + dy[i];
            int next_z = tmp.second + dz[i];

            // if out of range
            if(next_x < -1 || next_x > 30 || next_y < -1 || next_y > 30 || next_z < -1 || next_z > 30)
                continue;
            
            // no water or obsidean at next position
            // so set it as a water pos and add to queue to check adjacent spaces
            if(!water[mp(mp(next_x, next_y), next_z)] && !obsideans_copy[mp(mp(next_x, next_y), next_z)]){
                water[mp(mp(next_x, next_y), next_z)] = true;
                q.push(mp(mp(next_x, next_y), next_z));
            }
        }
    }

    int res{0};
    
    // check all blocks
    for(auto& o : obsideans){
        // check all adjacent positions
        for(int i{0}; i < 6; i++){
            // if water at an adjacent pos
            if(water[mp(mp(o.first.first.first + dx[i], o.first.first.second + dy[i]), o.first.second + dz[i])]){
                res++;
            }
        }
    }
 
    cout << res << endl;

    return 0;
}