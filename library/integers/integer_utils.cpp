// #include<iostream>
// #include<algorithm>
#include <atcoder/all>
#include <fstream>

#include "bits/stdc++.h"
#define _GLIBCXX_DEBUG
#define ll long long
using namespace std;

using mint=atcoder::modint1000000007;

//combination
ll com(ll n, ll k){
    ll ret=1;
    for(int i=1; i<=k; i++){
        ret=ret*(n+1-i)/i;
    }
    return ret;
}

//combination
mint mod_com(ll n, ll k) {
    mint ret = 1;
    for (mint i = 1; i.val() <= k; i++) {
        ret = ret * (n + 1 - i) /i;  //ret*(n+1-1)/i
    }
    return ret;
}

map<pair<int, int>, ll> comtable;
ll com(int n, int k) {
    if (n == k || k == 0 || n==0) return 1;
    if (comtable.count({n, k})) return comtable[{n, k}];
    comtable[{n,k}]= com(n-1,k-1)+com(n-1,k);
    comtable[{n,n-k}]=comtable[{n,k}];
    return comtable[{n,k}];
}


//素数列挙
vector<int> eratos(int N) {
    vector<bool> is_prime(N + 1, true);
    vector<int> primes;
    for (ll i = 2; i <= N; i++) {
        if (is_prime[i]) {
            for (ll j = i * i; j <= N; j += i) {
                is_prime[j] = false;
            }
            primes.emplace_back(i);
        }
    }
    return primes;
}

//素因数分解 O(√N)
vector<pair<ll, ll>> prime_fac(ll n) {
    vector<pair<ll, ll>> r;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i != 0) continue;
        int cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        r.push_back({i, cnt});
    }
    if (n != 1) r.push_back({n, 1});
    return r;
}

map<ll,ll> prime_fac_(ll n) {
    map<ll,ll> r;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i != 0) continue;
        int cnt = 0;
        while (n % i == 0) {
            n /= i;
            cnt++;
        }
        r[i]=cnt;
    }
    if (n != 1) r[n]=1;
    return r;
}

//素因数分解 前処理O(N) クエリO(Log N) N<2e7くらい(80MB)
vector<int> spf(2e7, 1);  //smallest prime factor
void init_spf() {
    int N = spf.size();
    for (int i = 0; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++) {
        if (spf[i] == i) {
            for (int j = i * i; j < N; j += i) {
                if (spf[j] == j) spf[j] = i;
            }
        }
    }
}

map<int, int> prime_fac(int n) {
    map<int, int> count;
    while (spf[n] != 1) {
        int val = spf[n];
        count[val]++;
        n /= spf[n];
    }
    return count;
}

int main() {
    vector<int> primes = eratos(50);
    for (auto x : primes) {
        cout << x << ' ';
    }
    cout << endl;

    cout << __gcd<long long>(1ll << 43 + 1, 1ll << 39 + 1) << endl;
}