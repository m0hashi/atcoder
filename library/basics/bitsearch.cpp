#include <iostream>
#include "bits/stdc++.h"
using namespace std;

int main() {
    int n = 3;
    for(int bit=0; bit < (1<<n); bit++){
        vector<int> S;
        for(int i=0; i<n; i++){
            if(bit & (1<<i)){
                S.push_back(i);
            }
        }
        for(auto x: S){
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}