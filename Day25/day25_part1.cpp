#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

#define ll long long

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

ll decimal_to_SNAFU(ll& decimal)
{
    ll ret;
    while(decimal >= 0){
        ll n = decimal%10;
        decimal /= 10;
    }



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
    vector<string> SNAFU_nums = read_data("../Day25/day25_test.txt");

    // translate from SNAFU to decimal
    vector<ll> decimal_nums;
    for(auto& s : SNAFU_nums) decimal_nums.push_back(SNAFU_to_decimal(s));

    // sum decimal numbers 
    ll total_decimal{0};
    for(auto& n : decimal_nums) total_decimal += n;

    // convert back to SNAFU
    ll total_SNAFU = decimal_to_SNAFU(total_decimal)

    return 0;
}