#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

#define ll long long

// convert SNAFU number to decimal
ll SNAFU_to_decimal(string& s)
{
    char c;
    reverse(s.begin(), s.end());  // reverse string
    stringstream ss(s);
    int factor{-1};
    ll res{0};

    // read in each character
    while(ss >> c){
        factor++;
        switch(c){
            case '=': 
                res += -2*pow(5, factor);
                continue;
            case '-': 
                res += -1*pow(5, factor);
                continue;
            case '1': 
                res += pow(5, factor);
                continue;
            case '2': 
                res += 2*pow(5, factor);
                continue;
        }
    }

    return res;
}

// convert decimal number to SNAFU
string decimal_to_SNAFU(ll& num){
    string ret = "";
    while(num){
        switch(num%5) {
            case 0:
                ret += '0';
                num /= 5;
                break;
            case 1:
                ret += '1';
                num /= 5;
                break;
            case 2:
                ret += '2';
                num /= 5;
                break;
            case 3:
                ret += '=';
                num /= 5;
                ++num;
                break;
            case 4:
                ret += '-';
                num /= 5;
                ++num;
                break;
            default:
                cout << num % 5 << endl;
                cout << "Impossible" << endl;
                break;
        }
    }

    reverse(ret.begin(), ret.end());

    return ret;
} 


vector<string> read_data(const string& file_name)
{
    fstream fs(file_name);
    string line;
    vector<string> ret;
    while(getline(fs, line)) ret.push_back(line); 
    return ret;
}

int main()
{
    vector<string> SNAFU_nums = read_data("../Day25/day25_data.txt");

    // translate from SNAFU to decimal
    vector<ll> decimal_nums;
    for(auto& s : SNAFU_nums) decimal_nums.push_back(SNAFU_to_decimal(s));

    // sum decimal numbers 
    ll total_decimal{0};
    for(auto& n : decimal_nums) total_decimal += n;

    // convert back to SNAFU
    string total_SNAFU = decimal_to_SNAFU(total_decimal);
    cout << total_SNAFU << endl;

    return 0;
}