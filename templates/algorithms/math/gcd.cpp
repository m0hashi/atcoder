#include "bits/stdc++.h"
#define _GLIBCXX_DEBUG
#define ll long long
using namespace std;

ll exGCD(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll d = exGCD(b, a & b, y, x);
    y -= a / b * x;
    return d;
}

