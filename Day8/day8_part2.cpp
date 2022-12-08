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

    int max_scenic_score{0};

    // check only inner trees
    // outer trees always have one 0 so scenic score is 0
    for(int i{1}; i < n-1; i++){
        for(int j{1}; j < m-1; j++){

            // initalise variables
            int left{0}, right{0}, up{0}, down{0}, score;
            int tree_height = forest[i][j];
            int copy_i, copy_j;

            // search left until find tree as big
            copy_j = j-1;
            while(copy_j >= 0){
                left++;
                if(forest[i][copy_j] >= tree_height) break;
                copy_j--;
            }

            // search right until find tree as big
            copy_j = j+1;
            while(copy_j <= m-1){
                right++;
                if(forest[i][copy_j] >= tree_height) break;
                copy_j++;
            }

            // search up until find tree as big
            copy_i = i-1;
            while(copy_i >= 0){
                up++;
                if(forest[copy_i][j] >= tree_height) break;
                copy_i--;
            }

            // search down until find tree as big
            copy_i = i+1;
            while(copy_i <= n-1){
                down++;
                if(forest[copy_i][j] >= tree_height) break;
                copy_i++;
            }

            // calculate score
            score = left*right*up*down;

            // better tree
            if(score > max_scenic_score) max_scenic_score = score;

        }
    }

    // print result
    cout << max_scenic_score << endl;

    return 0;
}