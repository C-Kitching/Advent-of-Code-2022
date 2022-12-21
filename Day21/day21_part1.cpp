#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <tuple>

using namespace std;

unordered_map<string, long long> values;
unordered_map<string, tuple<string, char, string>> expr;

auto calc(const string& name)
{
    // if name is just a value return it
    if(values.count(name)) return values[name];

    // otherwise calculate value recurssively
    else{
        tuple<string, char, string> e = expr[name];
        string left = get<0>(e);
        string right = get<2>(e);
        char op = get<1>(e);

        switch(op){
            case '+':
                return calc(left) + calc(right);
            case '-':
                return calc(left) - calc(right);
            case '*':
                return calc(left) * calc(right);
            case '/':
                return calc(left) / calc(right);
            default:
                exit(1);
        }
    }
}

void read_data(const string& file_name)
{
    ifstream fs(file_name);
    string line;
    while(getline(fs, line)){
        if(isdigit(line[6])){
            values[line.substr(0, 4)] = stoll(line.substr(6));
        }
        else{
            expr[line.substr(0, 4)] = {line.substr(6, 4), line.substr(11, 1).at(0), line.substr(13)};
        }
    }
}

int main()
{
    read_data("../Day21/day21_data.txt");
    cout << calc("root") << endl;

    return 0;
}