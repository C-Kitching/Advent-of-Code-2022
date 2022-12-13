#include<iostream>
#include<string>
#include<vector>
#include<numeric>
#include<fstream>

using namespace std;

bool isNumeric(char a){
  return (a >= '0' && a <= '9');
}

int main(){

  string line1, line2;
  int list = 0;
  vector<string> signals{"[[2]]", "[[6]]"};
  int cnt[2] = {0};
  ifstream cin("../Day13/day13_data.txt");
  while(getline(cin,line2)){
    if(line2.length() == 0) continue;
    list++;
    for(int x = 0; x < 2; x++){
      line1 = signals[x];
      int i = 0, j = 0;
      while(i < line1.length() && j < line2.length()){
        if(isNumeric(line1[i]) && isNumeric(line2[j])){
          string x1 = "", x2 = "";
          while(i < line1.length() && isNumeric(line1[i])){
            x1 += line1[i];
            i++;
          }
          while(j < line2.length() && isNumeric(line2[j])){
            x2 += line2[j];
            j++;
          }
          if(stoi(x1) == stoi(x2)) continue;
          if(stoi(x1) < stoi(x2)){
            cnt[x]++;
          }
          break;
        }
        if(line1[i] == line2[j]){
          i++;
          j++;
          continue;
        }
        else{
          if(line1[i] == ']'){
            cnt[x]++;
            break;
          }
          else if(line2[j] == ']') break;
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
      if(i == line1.length()) cnt[x]++; 
    }
  }
  cout << (list - cnt[0] + 1)*(list - cnt[1] + 2) << endl;
}