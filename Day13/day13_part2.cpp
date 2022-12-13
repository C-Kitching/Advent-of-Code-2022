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
#include <numeric>

using namespace std;

// test if a character is numeric
bool is_numeric(const char& a){
  return (a >= '0' && a <= '9');
}

int main()
{
    string line1, line2;
    vector<int> right;  // index of pairs where right is greater
    int list{0};  // index of pairs
    vector<string> signals{"[[2]]", "[[6]]"};
    int cnt[2] = {0};

    // read in each line
    // attempt to bubble sort signals to correct indexs
    ifstream file("../Day13/day13_data.txt");
    while(getline(file, line2)){

        // if at empty line between pairs then skip
        if(line2.length() == 0) continue;

        list++;  // track pair index

        for(int x{0}; x < 2; x++){

            line1 = signals[x];

            // parse both pairs
            int i = 0, j = 0;
            while(i < line1.length() && j < line2.length()){

                // if comparing numbers in a list
                if(is_numeric(line1[i]) && is_numeric(line2[j])){

                    // build numbers
                    string x1 = "", x2 = "";
                    while(i < line1.length() && is_numeric(line1[i])){
                        x1 += line1[i];
                        i++;
                    }
                    while(j < line2.length() && is_numeric(line2[j])){
                        x2 += line2[j];
                        j++;
                    }

                    // if both numbers of list the name, check next element
                    if(stoi(x1) == stoi(x2)) continue;

                    // if left element smaller than found a valid list
                    if(stoi(x1) < stoi(x2))
                        cnt[x]++;  // store list index

                    break;  // move to next pair
                }

                // if both char the same, i.e. opening bracker or comma
                // then continue to next char
                if(line1[i] == line2[j]){
                    i++; 
                    j++;
                    continue;
                }

                // eles if chars are different and both not numbers
                else{

                    // reached the end of signal before list so signal 
                    // valid pair
                    if(line1[i] == ']'){
                        cnt[x]++;
                        break;  // move to next signal
                    }

                    // reach the end of list 2 before list 1
                    // not a valid pair
                    else if(line2[j] == ']') break;  // move to next signal

                    // move until chars the same
                    else if(line1[i] == '[' || line1[i] == ','){
                        i++;
                        continue;
                    }
                    else if(line2[j] == '[' || line2[j] == ','){
                        j++;
                        continue;
                    }
                }
            }

            // finished list 1 first
            if(i == line1.length()) cnt[x]++;
        }
    }

    cout << (list - cnt[0] + 1)*(list - cnt[1] + 2) << endl;

    return 0;
}