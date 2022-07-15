// #include<iostream>
// #include<algorithm>
#include <atcoder/all>
#include <fstream>
#include "bits/stdc++.h"
#define _GLIBCXX_DEBUG
using namespace std;



template<typename T>
long long pow(T x, T p){
    T res=1;
    while(p>0){
        if (p & 1) res = res* x;
        x = x*x;
        p >>=1;
    }
    return res;
}

template<typename T>
long long mod_pow(T x, T p, T m){
    T res=1;
    while(p>0){
        if (p & 1) res = res* x % m;
        x = x*x%m;
        p >>=1;
    }
    return res;
}

template<typename T>
long long mod_inv(T x, T m){
    return mod_pow(x, m-2, m);
}

template<typename T>
long long fac(T n){
    if (n==0) return 1;
    return fac(n-1)*n;
}

template<typename T>
long long comb(T n, T x){
    return fac(n)/(fac(x)*fac(n-x));
}

template<typename T>
long long mod_fac(T n, T m){
    if (n==0) return 1;
    return (fac(n-1)*n)%m;
}



template<typename T>
long long mod_comb(T n, T k, T mod){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    //init table
    vector<long long> fac(n+1), finv(n+1), inv(n+1);
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i <= n; i++){
        fac[i] = fac[i - 1] * i % mod;
        inv[i] = mod - inv[mod%i] * (mod / i) % mod;
        finv[i] = finv[i - 1] * inv[i] % mod;
    }
    return  fac[n] * (finv[k] * finv[n - k] % mod) % mod;
}
