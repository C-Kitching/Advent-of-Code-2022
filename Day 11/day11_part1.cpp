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

using namespace std;

// enum class for operations of monkeys
enum operation_enum{e_add, e_mul, e_squ};

// monkey structure
struct monkey{
    vector<int> items;  // items held by monkey
    operation_enum op;  // operation of monkey
    int op_arg;  // number involved in operation
    int test_arg;  // number to divide by in test
    int true_num;  // monkey to throw to if passed test
    int false_num;  // monkey to throw to if failed test
    int inspection_count;  // number of inspections made by monkey
};

// short hand for vector of monkeys
using monkeys = vector<monkey>;

// function to split string into tokens
vector<string> split(const string& s){
    string token;
    vector<string> tokens;
    stringstream ss(s);
    while(ss >> token) tokens.push_back(token);
    return tokens;
}

// function to parse data
monkeys read_input(const string& file){

    monkeys ret;
    ifstream fs(file);
    string line;

    // read each line of file
    while(getline(fs, line)){

        // split line into tokens
        auto tokens = split(line);

        if(!tokens.empty()){

            // new monkey
            if(tokens[0] == "Monkey"){
                ret.push_back(monkey());
            }

            // items held by monkey
            else if(tokens[0] == "Starting"){
                for(int i{2}; i < tokens.size(); i++){
                    ret.back().items.push_back(stoi(tokens[i]));
                }
            }

            // operations performed by monkey
            else if(tokens[0] == "Operation:"){

                // squaring
                if(tokens[5] == "old"){
                    ret.back().op = e_squ;
                    ret.back().op_arg = 0;
                }

                // multiplication
                else if(tokens[4] == "*"){
                    ret.back().op = e_mul;
                    ret.back().op_arg = stoi(tokens[5]);
                }

                // addition
                else if(tokens[4] == "+"){
                    ret.back().op = e_add;
                    ret.back().op_arg = stoi(tokens[5]);
                }

            }

            // test condition
            else if(tokens[0] == "Test"){
                ret.back().test_arg = stoi(tokens[3]);
            } 

            // true result
            else if(tokens[1] == "true:"){
                ret.back().true_num = stoi(tokens[5]);
            }

            // false result
            else if(tokens[1] == "false:"){
                ret.back().false_num = stoi(tokens[5]);
            }
        }
    }

    return ret;
}

// function to perform calculation
auto process(monkeys monkeys, const bool& part1, const int& rounds){

    int mod_product{1};
    for(auto& monkey : monkeys){
        mode_product *= monkey.test_arg;
    }

    for(int r{0}; r < rounds; r++){
        
    }


}

int main()
{


    return 0;
}