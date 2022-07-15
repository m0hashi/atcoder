#include <atcoder/all>
#include "bits/stdc++.h"
#define _GLIBCXX_DEBUG
using namespace std;
#define ll long long
#define vvi vector<vector<int>>
#define vvl vector<vector<ll>>

vector<int> A = {2,3,3,4};
ll f(ll x) {
    ll s = 0;
    for(auto a : A)
        s += pow(a - x, 2);
    return s;
}

ll trisect() {
    int l = -101;//両側開区間で探索する
    int r = 101;
    int cl = l, cr = r;
    int min_idx = r;
    while(cr - cl > 1) {
        cl = l + (r - l) / 3;
        cr = r - (r - l) / 3;
        if(f(cl) < f(cr))
            r = cr;
        else
            l = cl;
    }
    if(f(cl) < f(cr)) {
        return cl;
    } else {
        return cr;
    }
}

int main(){
    ll ans=trisect();
    printf("%ld:%ld\n",ans,f(ans));
    return 0;
}