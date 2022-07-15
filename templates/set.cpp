// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using P = pair<ll, ll>;
#define INF 1 << 30

int main() {
    set<int> S1, S2;
    S1 = {1, 2, 3};
    S2 = {3, 4, 5};
    vector<int> S;
    //積集合
    S.clear();
    set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), back_inserter(S));
    for (auto s : S) {
        cout << s;
    }
    cout << endl;
    //和集合
    S.clear();
    set_union(S1.begin(), S1.end(), S2.begin(), S2.end(), back_inserter(S));
    for (auto s : S) {
        cout << s;
    }
    cout << endl;
    //差集合
    S.clear();
    set_difference(S1.begin(), S1.end(), S2.begin(), S2.end(), back_inserter(S));
    set_difference(S2.begin(), S2.end(), S1.begin(), S1.end(), back_inserter(S));
    for (auto s : S) {
        cout << s;
    }
    //UNIQUE
    vector<int> X={1,2,3,3,4};
    sort(X.begin(), X.end()); X.erase(unique(X.begin(), X.end()),X.end());
    for (auto s : X) {
        cout << s;
    }
    cout << endl;
    cout << endl;
}
