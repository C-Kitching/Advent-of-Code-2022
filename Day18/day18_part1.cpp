#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
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

    int res{0};
    
    // check all blocks
    for(auto& o : obsideans){
        // check all adjacent positions
        for(int i{0}; i < 6; i++){
            // if block at any adjacenct position does not exist
            if(!obsideans_copy[mp(mp(o.first.first.first + dx[i], o.first.first.second + dy[i]), o.first.second + dz[i])]){
                res++;
            }
        }
    }
 
    cout << res << endl;

    return 0;
}