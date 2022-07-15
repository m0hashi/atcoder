#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using P = pair<ll, ll>;
#define INF 1 << 30

class CycleDetection {
   public:
    CycleDetection(int n) : _n(n), edge(n) {}
    void add_edge(int u, int to, int w) {
        edge[u].push_back({to, w});
    }
    bool run() {
        pre.assign(_n, INF);
        post.assign(_n, INF);
        for (int i = 0; i < _n; i++) {
            if (pre[i] != INF) continue;
            if (dfs(i)) return true;
        }
        return false;
    }
    bool dfs(int u) {
        bool has_cycle = false;
        pre[u] = _clock++;
        for (auto e : edge[u]) {
            if (pre[e.to] != INF && post[e.to] == INF) has_cycle = true;
            if (pre[e.to] != INF) continue;
            has_cycle |= dfs(e.to);
        }
        post[u] = _clock++;
        return has_cycle;
    }

   private:
    int _n, _clock = 0;
    struct Edge {
        int w, to;
        Edge(int to, int w) : to(to), w(w) {}
    };
    vector<vector<Edge>> edge;
    vector<int> pre, post;
};

int main() {
    int v, e;
    cin >> v >> e;
    CycleDetection cd(v);
    for (int i = 0; i < e; i++) {
        int s, t;
        cin >> s >> t;
        cd.add_edge(s, t, 1);
    }
    bool ans = cd.run();
    if (ans) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }
}