// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

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
vector<int> dd4 = {1, 0, -1, 0, 1};                // 4方位 rep(i,4) nh=h+dd4[i]; nw=w+dd4[i+1];
vector<int> dd8 = {1, 0, -1, 0, 1, 1, -1, -1, 1};  // 8方位 rep(i,8) nh=h+dd8[i]; nw=w+dd8[i+1];

template <typename T>
vector<vector<T>> floydWarshall(const vector<vector<T>>& dist, const T INF) {
    int n = dist.size();
    vector<vector<T>> ret = dist;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (ret[i][k] == INF || ret[k][j] == INF) continue;
                ret[i][j] = min(ret[i][j], ret[i][k] + ret[k][j]);
            }
        }
    }
    return ret;
}

struct Solver {
    void solve(int case_id) {
        ll INF = 1LL << 60;
        int v, e;
        cin >> v >> e;
        vector<vector<ll>> dist(v, vector<ll>(v, INF));
        rep(i, v) dist[i][i] = 0;
        rep(i, e) {
            int a, b, c;
            cin >> a >> b >> c;
            dist[a][b] = c;
        }
        auto ret = floydWarshall(dist, INF);
        rep(i, v) rep(j, v) if (ret[i][j] + ret[j][i] < 0) {
            cout << "NEGATIVE CYCLE" << endl;
            return;
        }
        rep(i, v) {
            rep(j, v) {
                if (j != 0) cout << ' ';
                if (ret[i][j] == INF)
                    cout << "INF";
                else
                    cout << ret[i][j];
            }
            cout << endl;
        }
    };
};

int main() {
    std::cin.tie(nullptr);
    int T;
    // cin >> T;
    T = 1;
    for (int i = 0; i < T; i++) {
        Solver solver;
        solver.solve(i);
    }
    return 0;
}
