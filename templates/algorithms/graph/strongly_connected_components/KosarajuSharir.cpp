#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using P = pair<ll, ll>;
#define INF 1 << 30

class KosarjuSharir {
   public:
    KosarjuSharir(int n) : _n(n), edge(n), rev_edge(n) {}
    void add_edge(int u, int to, int w) {
        edge[u].push_back({to, w});
        rev_edge[to].push_back({u, w});
    }
    void run() {
        stack<int> S;
        root.assign(_n, -1);
        root.assign(_n, -1);
        pre.assign(_n, INF);
        for (int i = 0; i < _n; i++) {
            if (pre[i] != INF) continue;
            pushPostDfs(i, S);
        }
        while (!S.empty()) {
            int v = S.top();
            S.pop();
            if (root[v] != -1) continue;
            vector<int> nodes;
            labelDfs(v, v, nodes);
            reverse(nodes.begin(), nodes.end());
            _group.push_back(nodes);
        }
        reverse(_group.begin(), _group.end());
    }
    void pushPostDfs(int v, stack<int> &S) {
        pre[v] = _clock++;
        for (auto e : rev_edge[v]) {
            if (pre[e.to] != INF) continue;
            pushPostDfs(e.to, S);
        }
        S.push(v);
    }
    void labelDfs(int v, int r, vector<int> &nodes) {
        root[v] = r;
        for (auto e : edge[v]) {
            if (root[e.to] != -1) continue;
            labelDfs(e.to, r, nodes);
        }
        nodes.push_back(v);
    }
    bool same(int v, int u) {
        return root[v] == root[u];
    }
    vector<vector<int>> scc() {
        return _group;
    }

   private:
    int _n, _clock = 0;
    bool _has_cycle = false;
    struct Edge {
        int w, to;
        Edge(int to, int w) : to(to), w(w) {}
    };
    vector<vector<Edge>> edge, rev_edge;
    vector<int> pre, post;
    vector<int> root;
    vector<vector<int>> _group;
    map<int, int> _siz;
};

// https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/3/GRL_3_C
int main() {
    int v, e;
    cin >> v >> e;
    KosarjuSharir scc(v);
    for (int i = 0; i < e; i++) {
        int s, t;
        cin >> s >> t;
        scc.add_edge(s, t, 1);
    }
    scc.run();
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        cout << scc.same(u, v) << endl;
    }
    return 0;
}
