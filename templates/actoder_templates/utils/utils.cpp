#include <bits/stdc++.h>
using namespace std;

vector<string> split(string& str, string delim ) {
    vector<string> tokens;
    int spos=0, epos;
    while((epos=str.find_first_of(delim, spos)) != string::npos){
        tokens.push_back(str.substr(spos, epos-spos));
        spos=epos+delim.length();
    }
    if (tokens.size()==0) tokens.push_back(str);
    return tokens;
}
