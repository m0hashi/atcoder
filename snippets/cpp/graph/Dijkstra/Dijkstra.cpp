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
    int id;
    int to;
    ll cost;
    Edge(int t, ll c, int i = 0) : to(t), cost(c), id(i) {}
};

struct Graph{
    vector<vector<Edge>> edge;
    Graph(int n): edge(n){}
    void add_edge(int from, int to, int cost=1){
        edge[from].emplace_back(to,cost);
    }
    vector<Edge>& operator [](int i){
        return edge[i];
    }
    int size(){
        return edge.size();
    }
};

vector<int> dijkstra(Graph& g, int s) {
    pq_inv<pair<int, int>> pq;
    vector<int> dist(g.size(), 1 << 30);
    dist[s]=0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for (auto&& e : g[u]) {
            if (dist[e.to] <= d + e.cost) continue;
            dist[e.to] = d + e.cost;
            pq.push({dist[e.to], e.to});
        }
    }
    return dist;
}


struct Dijkstra {
    ll INF = 1LL << 59;
    vector<vector<Edge>> edge;
    vector<ll> dist;
    Dijkstra(int n) : edge(n), dist(n, INF) {}

    void add_edge(int from, int to, ll cost, int id = 0) {
        edge[from].emplace_back(to, cost, id);
    }

    vector<ll> run(int s) {
        priority_queue<
            tuple<ll, int>,  // dist, current_node
            vector<tuple<ll, int>>,
            greater<tuple<ll, int>>
            >q;
        dist[s] = 0;
        q.push({0, s});
        while (!q.empty()) {
            auto [d, v] = q.top();
            q.pop();
            if (d > dist[v]) continue;
            rep(i, edge[v].size()) {
                const Edge& e = edge[v][i];
                if (chmin(dist[e.to], dist[v] + e.cost)) {
                    q.push({dist[e.to], e.to});
                }
            }
        }
        return dist;
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
            cout << dist[t] << endl;
        }
    };
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
