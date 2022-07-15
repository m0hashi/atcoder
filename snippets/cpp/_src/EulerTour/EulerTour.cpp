// #define _GLIBCXX_DEBUG
#include <atcoder/all>

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
auto chmax = [](auto& a, auto b) {bool ret=a<b; if(ret)a=b; return ret;};
auto chmin = [](auto& a, auto b) {bool ret=a>b; if(ret)a=b; return ret;};
template<typename T> using pq_inv = priority_queue<T, vector<T>, greater<T>>;

struct EulerTour{
    struct Edge{
        int to, w;
        Edge(int to, int w): to(to), w(w){};
    };
    int _n;
    vector<vector<Edge>> edge;
    vector<int> time_in, time_out, tour_order, parent;
    EulerTour(int n): _n(n), edge(n), time_in(n), time_out(n), parent(n), tour_order(2*n){
        
    };
    void add_edge(int from, int to, int w=1){
        edge[from].emplace_back(to, w);
        edge[to].emplace_back(from, w);
    }
    void init(int root){
        int clock=0;
        dfs(root, -1, clock) ;
    }
    void calc(int cur){

    }
    void dfs(int cur, int par, int& clock){
        time_in[cur]=clock;
        tour_order[clock++]=cur;
        parent[cur]=par;
        calc(cur);//追加で何か計算するものがあれば
        for(auto&& e:edge[cur]){
            if(e.to==par)continue;
            dfs(e.to, cur, clock);
        }
        time_out[cur]=clock;
        tour_order[clock++]=-cur;
    }
    int get_node_idx(int x){
        return (tour_order[x]>0)?tour_order[x]:parent[x];
    }


};

struct Solver{
    void solve(){
    };
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
