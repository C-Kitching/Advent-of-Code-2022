#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int dx[6] = {1, -1, 0, 0, 0, 0};
int dy[6] = {0, 0, 1, -1, 0, 0};
int dz[6] = {0, 0, 0, 0, 1, -1};

vector<vector<int>> read_data(const string& file)
{
    ifstream fs(file);
    string line;
    int x, y, z;
    char c;
    vector<vector<int>> coords;
    while(getline(fs, line)){
        stringstream ss(line);
        ss >> x >> c >> y >> c >> z;
        coords.push_back({x, y, z});
    }

    return coords;
}


int main()
{
    // read in data
    vector<vector<int>> coords = read_data("C:/Users/Christopher/OneDrive/Desktop/GitHub/Advent-of-Code-2022/Day18/day18_test.txt");

    // loop through blocks
    int res{0};
    for(int i{0}; i < coords.size(); i++){
        vector<int> coord = coords[i];
        res += 6;

        // if no adjacent coords
        for(int i{0}; i < 6; i++){
            vector<int> adj_coord = {coord[0] + dx[i], coord[1] + dy[i], coord[2] + dz[i]};

            for(int j{0}; j < coords.size(); j++){
                if(i != j){
                    if(coords[j] == adj_coord){
                        res--;
                        break;
                    }
                }
            }
        }
    }

    cout << res;

    return 0;
}