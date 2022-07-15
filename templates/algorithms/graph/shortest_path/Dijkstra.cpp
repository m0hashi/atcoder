#include <bits/stdc++.h>

#include <fstream>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
#define INF 1<<30


class Dijkstra {
   public:
    Dijkstra(int n) : _n(n), edge(n), dist(n, INF) {}
    void add_edge(int v, int to, int w) {
        edge[v].push_back({w, to});
    }
    vector<ll> run(int s) {
        priority_queue<Edge, vector<Edge>, greater<Edge>> q;
        vector<bool> seen(_n, false);
        q.push({0, s});
        while (!q.empty()) {
            auto [d, u] = q.top();
            q.pop();
            if (seen[u]) continue;
            seen[u] = true;
            dist[u] = d;
            for (auto e : edge[u]) {
                if (e.w + d >= dist[e.to]) continue;
                q.push({d + e.w, e.to});
            }
        }
        return dist;
    }

   private:
    int _n;
    ll _INF = 1 << 30;
    struct Edge {
        int w, to;
        Edge(int w, int to) : w(w), to(to) {}
        bool operator>(const Edge& rhs) const { return w > rhs.w; }
        bool operator<(const Edge& rhs) const { return w < rhs.w; }
    };
    vector<vector<Edge>> edge;
    vector<ll> dist;
};

// https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1
int main() {
    int v, e, r;
    cin >> v >> e >> r;
    Dijkstra dk(v);
    for (int i = 0; i < e; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        dk.add_edge(s, t, d);
    }
    auto dist = dk.run(r);
    for (int i = 0; i < v; i++) {
        if (dist[i] == INF) {
            cout << "INF" << endl;
        } else {
            cout << dist[i] << endl;
        }
    }
    return 0;
}