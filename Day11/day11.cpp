#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <list>

using namespace std;

// enum class to represent monkey operations
enum operation_enum { e_add, e_mul, e_squ }; 

// monkey structuer
struct monkey_t{
    std::list<uint64_t> items;
    operation_enum op;
    int op_arg;
    int test_arg;
    int true_num;
    int false_num;
    int inspection_count = 0;
};

// shorthand for vector of monkey objects
using monkeys_t = std::vector<monkey_t>;

// function to split string into tokens
std::vector<std::string> split(const std::string& s){
    std::string token;
    std::vector<std::string> tokens;
    std::stringstream ss(s);
    while(ss >> token){
        tokens.push_back(token);
    }
    return tokens;
}
// function to read data from file
monkeys_t load_input(const std::string& file){

    monkeys_t ret;
    std::ifstream fs(file);
    std::string line; 

    while (std::getline(fs, line)) {
        auto tokens = split(line);
        if(!tokens.empty()){
            if(tokens[0] == "Monkey"){
                ret.push_back(monkey_t());
            }else if(tokens[0] == "Starting"){
                for(int i=2; i<tokens.size(); ++i){
                    ret.back().items.push_back(std::stoi(tokens[i]));
                }
            }else if(tokens[0] == "Operation:"){
                if(tokens[5] == "old"){
                    ret.back().op = e_squ;
                    ret.back().op_arg = 0;
                }else if(tokens[4] == "*"){
                    ret.back().op = e_mul;
                    ret.back().op_arg = std::stoi(tokens[5]);
                }else if(tokens[4] == "+"){
                    ret.back().op = e_add;
                    ret.back().op_arg = std::stoi(tokens[5]);
                }
            }else if(tokens[0] == "Test:"){
                ret.back().test_arg = std::stoi(tokens[3]);
            }else if(tokens[1] == "true:"){
                ret.back().true_num = std::stoi(tokens[5]);
            }else if(tokens[1] == "false:"){
                ret.back().false_num = std::stoi(tokens[5]);
            }
        }
    }

    return ret;
}

// function to perform the monkey item passing
auto process(monkeys_t monkeys, bool part1, int rounds) 
{  
    // calculate modulo product for speed 
    int mod_product = 1;
    for(auto& monkey : monkeys){
        mod_product *= monkey.test_arg;
    }

    for(int r{0}; r < rounds; r++){
        for(auto& monkey : monkeys){
            for(auto it=monkey.items.begin(); it != monkey.items.end(); it=monkey.items.erase(it)){
                monkey.inspection_count++;  // monkey inspects item

                // perform monkey operation
                auto& item = *it;
                if(monkey.op == e_add){
                    item += monkey.op_arg;
                }else if(monkey.op == e_mul){
                    item *= monkey.op_arg;
                }else if(monkey.op == e_squ){
                    item *= item;
                }
                
                // manage stress level
                if(part1) item /= 3;
                
                // throw item to next monkey if test past
                int next_monkey = (item % monkey.test_arg) == 0 ? monkey.true_num : monkey.false_num;
                monkeys[next_monkey].items.push_back(item % mod_product);
            }
        }        
    }
    
    // sum inspections from each monkey
    std::vector<uint64_t> counts;
    for(auto& monkey : monkeys){
        counts.push_back(monkey.inspection_count);
    }

    // sort and return product of highest inspections
    std::sort(counts.begin(), counts.end(), std::greater<uint64_t>());
    return counts[0] * counts[1];
}

int main()
{
    // read in data
    auto data = load_input("../Day11/day11_data.txt");

    // print results
    cout << "Part 1: " << process(data, true, 20) << endl;
    cout << "Part 2: " << process(data, false, 10000) << endl;

    return 0;
}