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

struct UnionFind {
    vector<int> par, siz;
    UnionFind(int n) : par(n, -1), siz(n) {}
    int root(int x) {
        if (par[x] == -1) return x;
        // return root(par[x]);
        return par[x] = root(par[x]);
    }
    bool is_same(int x, int y) {
        return root(x) == root(y);
    }

    bool merge(int x, int y) {
        x = root(x);
        y = root(y);
        if (is_same(x, y)) return false;
        if (y > x) swap(x, y);
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
    int size(int x) {
        return siz[root(x)];
    }
};

struct Edge {
    int from;
    int to;
    ll cost;
    Edge(int f, int t, ll c) :from(f), to(t), cost(c) {};
    bool operator<(const Edge& e) const{ return cost < e.cost;}
    bool operator>(const Edge& e) const{ return cost > e.cost;}
};

struct KruskalMST {
    vector<Edge> edge;
    vector<vector<Edge>> mst;
    ll mst_cost=0;
    KruskalMST(int n) : mst(n) {}

    void add_edge(int from, int to, ll cost) {
        edge.emplace_back(from, to, cost);
    }

    ll construct() {
        ll total_cost = 0;
        sort(edge.begin(), edge.end());
        UnionFind uf(mst.size());
        for(auto&& e:edge){
            if(uf.is_same(e.from, e.to))continue;
            uf.merge(e.from, e.to);
            mst[e.from].emplace_back(e.from, e.to, e.cost);
            mst[e.to].emplace_back(e.to, e.from, e.cost);
            total_cost += e.cost;
        }
        return total_cost;
    }
};

struct Solver {
    void solve(){
        int n;
        cin >> n;
        KruskalMST mst(n);
        rep(i,n)rep(j,n){
            int a;
            cin >> a;
            if(a==-1)continue;
            if(j<i)continue;
            mst.add_edge(i,j,a);
        }
        cout << mst.construct() << endl;
    };
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
