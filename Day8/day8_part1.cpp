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
    vector<vector<int>> forest;  // heights of trees in forest
    vector<vector<bool>> tree_visible;  // assume no tree visible to begin

    // read in data
    string file_path{"../Day8/day8_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        while(getline(my_file, line)) {
            vector<int> tree_row;
            vector<bool> tree_row_visible;
            for(int i{0}; i < line.size(); i++){
                tree_row.push_back(stoi(line.substr(i,1)));
                tree_row_visible.push_back(false);
            }
            forest.push_back(tree_row); 
            tree_visible.push_back(tree_row_visible);
        }  
    }

    // size of forest
    int n = forest.size();
    int m = forest[0].size();

    int visible_trees{0};

    // search all rows from left to right
    for(int i{0}; i < n; i++){
        int row_max = 0;
        for(int j{0}; j < m; j++){

            // if tree larger than previously largest tree
            if(forest[i][j] > row_max || j == 0){

                // if haven't marked tree as visible from any other direction
                if(!tree_visible[i][j]){
                    visible_trees++;
                    tree_visible[i][j] = true;
                }

                // update new maximum
                row_max = forest[i][j];
            }
        }
    }

    // search all rows from right to left
    for(int i{0}; i < n; i++){
        int row_max = 0;
        for(int j{m-1}; j >= 0; j--){

            // if tree larger than previously largest tree
            if(forest[i][j] > row_max || j == m-1){

                // if haven't marked tree as visible from any other direction
                if(!tree_visible[i][j]){
                    visible_trees++;
                    tree_visible[i][j] = true;
                }

                // update new maximum
                row_max = forest[i][j];
            }
        }
    }

    // search all cols from top to bottom
    for(int j{0}; j < m; j++){
        int col_max = 0;
        for(int i{0}; i < n; i++){

            // if tree larger than previously largest tree
            if(forest[i][j] > col_max || i == 0){

                // if haven't marked tree as visible from any other direction
                if(!tree_visible[i][j]){
                    visible_trees++;
                    tree_visible[i][j] = true;
                }

                // update new maximum
                col_max = forest[i][j];
            }
        }
    }

    // search all cols from bottom to top
    for(int j{0}; j < m; j++){
        int col_max = 0;
        for(int i{n-1}; i >= 0; i--){

            // if tree larger than previously largest tree
            if(forest[i][j] > col_max || i == n-1){

                // if haven't marked tree as visible from any other direction
                if(!tree_visible[i][j]){
                    visible_trees++;
                    tree_visible[i][j] = true;
                }

                // update new maximum
                col_max = forest[i][j];
            }
        }
    }

    // print result
    cout << visible_trees << endl;

    return 0;
}