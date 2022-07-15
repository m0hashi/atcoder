#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using P = pair<ll, ll>;
#define INF 1ll << 50

class MCArborescence {
   public:
    MCArborescence(int n) : _n(n), edge(n){}
    void add_edge(int v, int to, int w) {
        edge[v].push_back({w, to});
    }
    ll run(int s=0) {
        queue<pair<Edge,int>> q;
        q.push({{0, s}, 0});  //{weight, node}, totalcost
        int n_used = 0;
        vector<pair<ll,ll>> cost(_n,{INF,INF});// node,{total_cost, weight}
        cost[s]={0,0};
        vector<bool> used(_n,false);
        ll total=0;
        while (!q.empty()) {
            Edge e;
            tie(e, total) = q.front();q.pop();
            int d,u;
            d=e.w; u=e.to;
            if(total<=cost[u].first&&d<cost[u].second)cost[u]={total,e.w};
            for (auto &ne : edge[u]) {
                // if(ne.used)continue;
                if(cost[ne.to].first<total+ne.w)continue;
                q.push({{ne.w, ne.to}, total+ne.w});
                ne.used=true;
            }
        }
        ll ret=0;
        for(auto x:cost){
            ret+=x.second;
        }
        return ret;
    }

   private:
    int _n;
    struct Edge {
        int w;
        int to;
        bool used=false;
        Edge() {}
        Edge(int w, int to) : w(w), to(to) {}
        bool operator<(const Edge& rhs) const { return w < rhs.w; }
        bool operator>(const Edge& rhs) const { return w > rhs.w; }
    };
    vector<vector<Edge>> edge;
};

// https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/2/GRL_2_B
int main() {
    int v, e, r;
    cin >> v >> e >> r;
    MCArborescence mca(v);
    for (int i = 0; i < e; i++) {
        int s, t, w;
        cin >> s >> t >> w;
        mca.add_edge(s, t, w);
    }
    ll ans = mca.run(r);
    cout << ans << endl;
    return 0;
}