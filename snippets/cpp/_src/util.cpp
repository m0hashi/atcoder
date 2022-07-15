#include <bits/stdc++.h>
using namespace std;

template <typename T>
T mod_pow(T x, T p, T mod) {
    T res = 1;
    while(p > 0) {
        if(p & 1)
            res = (res*x) % mod;
        x = (x*x) % mod;
        p /= 2;
    }
    return res;
}

int main(){
    mod_pow(1,1,1);
}