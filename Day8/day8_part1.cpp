#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <utility>
#include <chrono>
#include <deque>

using namespace std;

int main()
{
    // decalre variables
    string buffer;
    string line;
    string height;
    vector<vector<int>> forest;

    // read in data
    string file_path{"../Day8/day8_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while(getline(my_file, line)) {
            vector<int> tree_row;
            for(int i{0}; i < line.size(); i++){
                tree_row.push_back(stoi(line.substr(i,1)));
            }
            forest.push_back(tree_row); 
        }  
    }

    // initalise vectors to track largest tree from each direction
    int n = forest.size();
    int m = forest[0].size();
    vector<int> max_from_top = forest[0];  // top row
    vector<int> max_from_bottom = forest[n-1];  // bottom row
    vector<int> max_from_left;  // left column
    vector<int> max_from_right;  // right column
    for(int i{0}; i < n; i++){
        max_from_left.push_back(forest[i][0]);
        max_from_right.push_back(forest[i][m-1]);
    }

    // search the forest
    int trees_visible{0};
    for(int i{1}; i < n; i++){
        for(int j{1}; j < m; j++){

            // update visable trees
            int tree_height = forest[i][j];
            if(tree_height < max_from_left[i] || 
               tree_height < max_from_right[i] || 
               tree_height < max_from_top[j] || 
               tree_height < max_from_bottom[j]) trees_visible++;

            // update maximum on each row
            max_from_left[i] = max(max_from_left[i], tree_height);
            max_from_right[i] = max(max_from_right[i], tree_height);
            max_from_top[i] = max(max_from_top[j], tree_height);
            max_from_bottom[i] = max(max_from_bottom[j], tree_height);

        }
    }

    // print result
    cout << trees_visible << endl;

    return 0;
}