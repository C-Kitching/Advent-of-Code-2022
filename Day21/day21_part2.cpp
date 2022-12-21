#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <tuple>
#include <cmath>

using namespace std;

unordered_map<string, long double> values;
unordered_map<string, tuple<string, char, string>> expr;

long double calc(const string& root, long double humn)
{
    // if we're at the root
    if(root == "root") {
        tuple<string, char, string> e = expr[root];
        string left = get<0>(e);
        string right = get<2>(e);

        // calculate left and right subtress with the test humn value
        long double A = calc(left, humn);
        long double B = calc(right, humn);

        if(fabs(A - B) < 1e-5) return 0;  // if values equal

        // values not equal
        if(A < B) return -1;
        else return 1;
    }

    // if at humn ignore the file value and return our test value
    else if(root == "humn") return humn;

    // if we known value
    else if(values.count(root)) return values[root];

    // otherwise calculate value recurssively
    else{
        tuple<string, char, string> e = expr[root];
        string left = get<0>(e);
        string right = get<2>(e);
        char op = get<1>(e);

        switch(op) {
            case '+':
                return calc(left, humn) + calc(right, humn);
            case '-':
                return calc(left, humn) - calc(right, humn);
            case '*':
                return calc(left, humn) * calc(right, humn);
            case '/':
                return calc(left, humn) / calc(right, humn);
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
            values[line.substr(0, 4)] = stold(line.substr(6));
        }
        else{
            expr[line.substr(0, 4)] = {line.substr(6, 4), line.substr(11, 1).at(0), line.substr(13)};
        }
    }
}

int main()
{
    read_data("../Day21/day21_data.txt");

    // binary search
    uint64_t low = 0, high = 1ULL << 62;
    while(high - low > 0) {

        // find midpoint
        long long mid = (low + high) >> 1;

        // test if that value is correct
        long long tmp = calc("root", mid);

        // found value to shout
        if(tmp == 0) {
            cout << mid << endl;
            return 0;
        } 

        // value to high so lower upper bound
        if(tmp < 0) high = mid - 1;

        // value to low so increase lower bound
        else low = mid + 1;
    }


    return 0;
}