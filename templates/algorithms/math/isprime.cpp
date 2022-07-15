#include "bits/stdc++.h"
using namespace std;
#define ll long long

ll mod_pow(ll x, ll p, ll m) {
    ll res = 1;
    while (p > 0) {
        if (p & 1)
            res = (x * res) % m;
        x = (x * x) % m;
        p >>= 1;
    }
    return res;
}
bool is_prime(ll n) {
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    vector<int> a_list = {2, 3, 5, 7, 11, 13, 17};

    int r = 0;
    ll tmp = n - 1;
    while (tmp % 2 == 0) {
        tmp /= 2;
        r++;
    }
    ll d = tmp;
    for (auto&& a : a_list) {
        ll x = mod_pow(a, d, n);
        bool con=false;
        if (x == 1 or x == (n - 1)) con=true;
        for (int i = 0; i < r; i++) {
            x = mod_pow(x, 2, n);
            if (x == n - 1) con=true;
        }
        if (con) continue;
        return false;
    }
    return true;
}

int main() {
    ll N;
    cin >> N;
    cout << (is_prime(N)?"Y":"N") << endl;
    return 0;
}