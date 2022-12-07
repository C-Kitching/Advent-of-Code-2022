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
#include <queue>

using namespace std;

int main()
{
    // decalre variables
    unordered_map<string, long> system;
    deque<string> curr_dir_path;
    string curr_dir;
    bool listing{false};

    // read in data
    string file_path{"../Day7/day7_data.txt"};
    ifstream my_file(file_path);
    if(my_file.is_open()) {
        string line;
        while(getline(my_file, line)) {
            stringstream ss(line); 

            // if listing files in current directory
            if(listing && line.substr(0, 1) != "$"){

                // if not a directory
                if(line.substr(0, 3) != "dir"){

                    // read file name and size
                    long size;
                    string name;
                    ss >> size >> name;

                    // incremement file size to all directory 
                    string total_dir;
                    for(string& dir : curr_dir_path){
                        total_dir += "_" + dir;

                        // dir already in system
                        if(system.find(total_dir) != system.end()){
                            system[total_dir] += size;
                        }
                        // dir not in system
                        else system[total_dir] = size;
                    }
                }
            }           

            // executing command 
            if(line.substr(0, 1) == "$"){

                // no longer listing files in directory
                listing = false;

                // move into new directory
                if(line.substr(2, 2) == "cd"){

                    // move to outermost directory
                    if(line.substr(5) == "/"){
                        curr_dir_path.erase(curr_dir_path.begin(), curr_dir_path.end());
                        curr_dir = "/";
                        curr_dir_path.push_back("/");
                    }

                    // move one layer out
                    else if(line.substr(5) == ".."){
                        curr_dir_path.pop_back();
                        curr_dir = curr_dir_path.back();
                    }

                    // move one layer in
                    else{
                        curr_dir = line.substr(5);
                        curr_dir_path.push_back(curr_dir);
                    }
                }

                // listing directorys
                else if(line.substr(2, 2) == "ls") listing = true;
            }
        }   
    }

    // find total size of all dirs with individual size less than 100000
    long total{0};
    for(auto& p : system){
        if(p.second <= 100000){
            total += p.second;
        }
    }

    cout << total << endl;


    return 0;
}