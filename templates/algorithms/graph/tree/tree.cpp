// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using P = pair<ll, ll>;
#define INF 1 << 30

class Tree {
   public:
    vector<int> dist;
    Tree(int n) : _n(n), edge(n), pre(n, INF), post(n, INF) {}
    void add_edge(int u, int to, int w = 1) {
        edge[u].push_back({to, w});
        edge[to].push_back({u, w});
    }
    void init() {
        pre.assign(_n, INF);
        post.assign(_n, INF);
        dist.assign(_n, -1);
    }
    vector<int> distance(int s) {
        init();
        dfs(s, 0);
        return dist;
    }
    int diameter() {
        auto d = distance(0);
        int maxd = -1;
        int s_idx = -1;
        for (int i = 0; i < _n; i++) {
            if (d[i] > maxd) {
                maxd = d[i];
                s_idx = i;
            }
        }
        d = distance(s_idx);
        maxd = -1;
        for (int i = 0; i < _n; i++) {
            if (d[i] > maxd) {
                maxd = d[i];
            }
        }
        return maxd;
    }
    void dfs(int u, int d) {
        pre[u] = _clock++;
        dist[u] = d;
        for (auto e : edge[u]) {
            if (pre[e.to] != INF) continue;
            dfs(e.to, d + e.w);
        }
        post[u] = _clock++;
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
    int n;
    cin >> n;
    Tree tree(n);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        a--;b--;
        tree.add_edge(a, b);
    }
    int ans=tree.diameter()+1;
    cout << ans << endl;
}