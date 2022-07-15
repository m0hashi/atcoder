#include <atcoder/all>
#include <fstream>
#include "bits/stdc++.h"
#define _GLIBCXX_DEBUG
#define ll long long
using namespace std;

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
