// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#include <atcoder/all>
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
    int to;
    ll cost;
    Edge(int t, int c) : to(t), cost(c) {}
};

struct PrimMST {
    ll INF = 1LL << 59;
    vector<vector<Edge>> edge;
    ll total_cost = 0;
    PrimMST(int n) : edge(n) {}
    void add_edge(int from, int to, ll cost) {
        edge[from].emplace_back(to, cost);
        edge[to].emplace_back(from, cost);
    }

    ll construct(int s) {
        priority_queue<
            pair<ll, int>,
            vector<pair<ll, int>>,
            greater<pair<ll, int>>>
            q;
        vector<ll> min_cost(edge.size(), INF);
        q.push({0, s});
        min_cost[s]=0;
        while (!q.empty()) {
            auto [cost, v] = q.top();
            q.pop();
            if(cost > min_cost[v])continue;
            for (auto&& e : edge[v]) {
                if(chmin(min_cost[e.to], e.cost)){
                    q.push({e.cost, e.to});
                    total_cost+=e.cost;
                }
            }
        }
        return total_cost;
    }
};

struct Solver {
    void solve(){
        int n;
        cin >> n;
        PrimMST mst(n);
        rep(i,n)rep(j,n){
            int a;
            cin >> a;
            if(a==-1)continue;
            if(j<i)continue;
            mst.add_edge(i,j,a);
        }
        cout << mst.construct(0) << endl;
    };
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
