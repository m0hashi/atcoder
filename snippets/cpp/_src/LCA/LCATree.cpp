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
#define repr(i, n) for (decltype(n) i = (n)-1; i >= 0; i--)
#define repr1(i, n) for (decltype(n) i = (n); i > 0; i--)
auto chmax = [](auto& a, auto b) {bool ret=a<b; if(ret)a=b; return ret; };
auto chmin = [](auto& a, auto b) {bool ret=a>b; if(ret)a=b; return ret; };
template <typename T>
using pq_inv = priority_queue<T, vector<T>, greater<T>>;

struct LCATree {
    struct Edge {
        int w, to;
        Edge(int to, int w) : to(to), w(w){};
    };
    vector<vector<Edge>> edge;
    vector<vector<int>> parent;
    vector<int> depth;
    int _k, _n;
    LCATree(int n):_n(n), edge(n), depth(n) {
      _k = (int)ceil(log2(n))+1;
      parent.assign(n, vector<int>(_k));
    } 
    void add_edge(int from, int to) {
        edge[from].emplace_back(to, 1);
        edge[to].emplace_back(from, 1);
    }
    void init(int root) {
        dfs(root, -1, 0);
        rep(i, _n) rep(j, _k - 1) {
            if (parent[i][j] < 0)
                parent[i][j + 1] = -1;
            else
                parent[i][j + 1] = parent[parent[i][j]][j];
        }
    }
    void dfs(int cur, int par, int d) {
        depth[cur] = d;
        parent[cur][0] = par;
        for (auto&& e : edge[cur]) {
            if (e.to == par) continue;
            dfs(e.to, cur, d + 1);
        }
    }

    int lca(int v, int u) {
        if (depth[u] < depth[v]) swap(u, v);
        rep(i, _k) if ((depth[u] - depth[v]) & (1 << i)) u = parent[u][i];
        if(u==v)return u;
        repr(i,_k) {
            if(parent[u][i]!=parent[v][i]){
                u = parent[u][i];
                v = parent[v][i];
            }
        }
        return parent[u][0];
    }
    int get_distance(int u, int v){
        return depth[u] + depth[v] - 2*lca(u,v);
    }
    bool is_on_path(int u, int v, int x){
        return get_distance(u,x) + get_distance(x,v) == get_distance(u,v);
    }
};

struct Solver {
    void solve() {
        int N;
        cin >> N;
        LCATree t(N);
        rep(i,N){
            int k;
            cin >> k;
            rep(j,k){
                int c;
                cin >> c;
                t.add_edge(i,c);
            }
        }
        t.init(0);
        int q;
        cin >> q;
        rep(i,q){
            int u,v;
            cin >> u >> v;
            cout << t.lca(u,v) << endl;
        }
        
    }
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
