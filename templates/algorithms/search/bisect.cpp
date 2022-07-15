#include <atcoder/all>
#include "bits/stdc++.h"
#define _GLIBCXX_DEBUG
using namespace std;
#define ll long long
#define vvi vector<vector<int>>
#define vvl vector<vector<ll>>


vector<int> A={1,1,1,2,3,3,4,5,5,6}; //10
bool isOK(ll mid){
    return A[mid]>4;
}

ll bisect(){
    ll ng=-1;
    ll ok=10;
    while(abs(ok-ng)>1){
        ll mid=ng+(ok-ng)/2;
        if(isOK(mid))ok=mid;
        else ng=mid;
    }
    return ok;
}

int main(){
    ll ans=bisect();
    printf("%ld:%d\n",ans,A[ans]);
    return 0;
}
