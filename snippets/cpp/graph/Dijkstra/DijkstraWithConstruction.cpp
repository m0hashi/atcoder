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

struct Edge {
    int id, from;
    int to;
    ll cost;
    Edge(int f, int t, ll c, int i = 0) : from(f), to(t), cost(c), id(i) {}
};

struct Dijkstra {
    ll INF = 1LL << 59;
    vector<vector<Edge>> edge;
    vector<ll> dist;
    vector<pair<int, int>> from;
    Dijkstra(int n) : edge(n), dist(n, INF), from(n, {-1, -1}) {}

    void add_edge(int from, int to, ll cost, int id = 0) {
        edge[from].emplace_back(from, to, cost, id);
    }

    vector<ll> run(int s) {
        priority_queue<
            tuple<ll, int, pair<int, int>>,  // dist, current_node, edge_id
            vector<tuple<ll, int, pair<int, int>>>,
            greater<tuple<ll, int, pair<int, int>>>>
            q;
        dist[s] = 0;
        q.push({0, s, {-1, s}});
        while (!q.empty()) {
            auto [d, v, idx] = q.top();
            q.pop();
            if (d > dist[v]) continue;
            rep(i, edge[v].size()) {
                const Edge& e = edge[v][i];
                if (chmin(dist[e.to], dist[v] + e.cost)) {
                    q.push({dist[e.to], e.to, {v, i}});
                    from[e.to] = {v, i};
                }
            }
        }
        return dist;
    }

    vector<Edge> construct_shortest_path(int t) {
        vector<Edge> path;
        for (int cur = t; cur != -1; cur = from[cur].first) {
            auto [_s, _t] = from[cur];
            if (_s != -1) path.push_back(edge[_s][_t]);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};

struct Solver {
    void solve() {
        int n, m, s, t;
        cin >> n >> m >> s >> t;
        Dijkstra graph(n);
        rep(i, m) {
            int a, b;
            ll c;
            cin >> a >> b >> c;
            graph.add_edge(a, b, c, i);
        }
        auto dist = graph.run(s);
        if (dist[t] == graph.INF) {
            cout << -1 << endl;
        } else {
            auto path = graph.construct_shortest_path(t);
            cout << dist[t] << ' ' << path.size() << endl;
            for (auto&& p : path) cout << p.from << ' ' << p.to << endl;
        }
    };
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
