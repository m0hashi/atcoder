// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#include <atcoder/all>
using namespace std;
#define ll long long
#define LLMAX numeric_limits<ll>::max()
#define LLMIN numeric_limits<ll>::min()
#define INTMAX numeric_limits<int>::max()
#define INTMIN numeric_limits<int>::min()
#define rep(i, n) for (decltype(n) i = 0; i < (n); i++)
#define rep1(i, n) for (decltype(n) i = 1; i <= (n); i++)
#define rep2(i, k, n) for (decltype(n) i = k; i <= (n); i++)
#define repr(i, n) for (decltype(n) i = (n)-1; i >= 0; i--)
#define repr1(i, n) for (decltype(n) i = (n); i > 0; i--)
#define repr2(i, k, n) for (decltype(n) i = n; i >= k; i--)
auto chmax = [](auto& a, auto b) {bool ret=a<b; if(ret)a=b; return ret; };
auto chmin = [](auto& a, auto b) {bool ret=a>b; if(ret)a=b; return ret; };
template <typename T>
using pq_inv = priority_queue<T, vector<T>, greater<T>>;
int MOD = 1e9 + 7;

struct Solver {
    void solve() {
        vector<string> S={"((","()",")(",")(","))"};
        sort(S.begin(), S.end());
        for(auto&& x:S){
            cout << x << endl;
        }
    }
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
