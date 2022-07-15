#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using P = pair<ll, ll>;
#define INF 1ll << 50

class Prim {
   public:
    Prim(int n) : _n(n), MST(n), edge(n) {}
    void add_edge(int v, int to, int w) {
        edge[v].push_back({w, to});
        edge[to].push_back({w, v});
    }
    ll run(int s=0) {
        priority_queue<pair<Edge, int>, vector<pair<Edge, int>>, greater<pair<Edge, int>>> q;
        vector<bool> used(_n, false);
        q.push({{0, s}, -1});  //{weight, node}, previous_node
        ll total = 0;
        int n_used = 0;
        while (!q.empty()) {
            Edge e;
            int p;
            tie(e, p) = q.top();
            q.pop();
            auto [d, u] = e;
            if (used[u]) continue;
            total += d;
            if(p!=-1){
                MST[p].push_back({d, u});
                MST[u].push_back({d, p});
            }
            used[u] = true;
            n_used++;
            if (n_used == _n) break;
            for (auto ne : edge[u]) {
                if (used[ne.to]) continue;
                q.push({{ne.w, ne.to}, u});
            }
        }
        return total;
    }

   private:
    int _n;
    struct Edge {
        int w;
        int to;
        Edge() {}
        Edge(int w, int to) : w(w), to(to) {}
        bool operator<(const Edge& rhs) const { return w < rhs.w; }
        bool operator>(const Edge& rhs) const { return w > rhs.w; }
    };
    vector<vector<Edge>> MST;
    vector<vector<Edge>> edge;
};

// https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_A MST
// 
int main() {
    int v, e, r;
    cin >> v >> e >> r;
    Prim prim(v);
    for (int i = 0; i < e; i++) {
        int s, t, w;
        cin >> s >> t >> w;
        prim.add_edge(s, t, w);
        // prim.add_edge(t, s, w);
    }
    ll ans = prim.run(r);
    cout << ans << endl;
    return 0;
}