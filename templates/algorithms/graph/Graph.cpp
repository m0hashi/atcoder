#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using P = pair<ll, ll>;
#define INF 1 << 30

class Graph {
   private:
    struct Edge {
        int to, w;
        Edge(int to, int w) : to(to), w(w){};
    };

   public:
    int n;
    vector<int> seen;
    vector<vector<Edge>> edge;
    Graph(int n) : n(n), seen(n), edge(n){};
    void add(int from, int to, int w=1) {
        edge[from].push_back(Edge(to,w));
    }
    void dfs(int s, int depth) {
        seen[s] = 1;
        for (auto e : edge[s]) {
            if (seen[e.to] == 1) continue;
            dfs(e.to, depth + 1);
        }
    }
};

class Graph {
   public:
    Graph(int n) : _n(n), edge(n), pre(n, INF), post(n, INF) {}
    void add_edge(int u, int to, int w) {
        edge[u].push_back({to, w});
    }
    void run() {
        pre.assign(_n, INF);
        post.assign(_n, INF);
        for (int i = 0; i < _n; i++) {
            if (pre[i] != INF) continue;
            dfs(i);
        }
    }
    void dfs(int u) {
        pre[u] = _clock++;
        S.push(u);
        for (auto e : edge[u]) {
            if (pre[e.to] != INF) continue;
            dfs(e.to);
        }
        post[u] = _clock++;
    }
    void bfs(int u) {
        pre[u] = _clock++;
        S.push(u);
        for (auto e : edge[u]) {
            if (pre[e.to] != INF) continue;
            dfs(e.to);
        }
        post[u] = _clock++;
    }
    void init() {
        while (!S.empty()) S.pop();
    }
    vector<int> get_pre_order() {
        vector<pair<int, int>> order(_n);
        vector<int> ret(_n);
        for (int i = 0; i < _n; i++) order[i] = {pre[i], i};
        sort(order.begin(), order.end());
        for (int i = 0; i < _n; i++) ret[i] = order[i].second;
        return ret;
    }
    vector<int> get_post_order() {
        vector<pair<int, int>> order(_n);
        vector<int> ret(_n);
        for (int i = 0; i < _n; i++) order[i] = {pre[i], i};
        sort(order.begin(), order.end());
        for (int i = 0; i < _n; i++) ret[i] = order[i].second;
        return ret;
    }

   private:
    int _n, _clock = 0;
    struct Edge {
        int w, to;
        Edge(int to, int w) : to(to), w(w) {}
    };
    vector<vector<Edge>> edge;
    vector<int> pre, post;
    stack<int> S;
};
