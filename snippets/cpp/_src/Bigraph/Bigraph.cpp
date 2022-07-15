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
#define repr(i, n) for (decltype(n) i = (n)-1; i >= 0; i++)
#define repr1(i, n) for (decltype(n) i = (n); i > 0; i++)
auto chmax = [](auto& a, auto b) {bool ret=a<b; if(ret)a=b; return ret; };
auto chmin = [](auto& a, auto b) {bool ret=a>b; if(ret)a=b; return ret; };
template <typename T>
using pq_inv = priority_queue<T, vector<T>, greater<T>>;

struct Bigraph {
    struct Edge {
        int rev, from, to, cap;
        Edge(int r, int f, int t, int c = 1) : rev(r), from(f), to(t), cap(c){};
    };
    int _n, _s, _t;
    vector<vector<Edge>> node;
    set<int> vertex_s, vertex_t;

    // Bigraph(int n, int s, int t): n(n), node(n), _s(s), _t(t){};
    Bigraph(int n) :_n(n), node(n), _s(n), _t(n+1) {};
    

    void add_edge(int from, int to, int cap = 1) {
        int idx_from = node[from].size();
        int idx_to = node[to].size();
        node[from].emplace_back(idx_to, from, to, cap);
        node[to].emplace_back(idx_from, to, from, 0);
    }

    void run_flow(Edge& e, int f) {
        e.cap -= f;
        node[e.to][e.rev].cap += f;
    }

    int update_residual_graph(int v, int t, int f) {
        if (v == t) return f;
        visited[v] = 1;
        for (auto&& e : node[v]) {
            if (visited[e.to] == 1) continue;
            if (e.cap == 0) continue;
            int flow = update_residual_graph(e.to, t, min(f, e.cap));
            if (flow == 0) continue;
            run_flow(e, flow);
            return flow;
        }
        return 0;
    }

    vector<int> visited;
    vector<Edge> matching_pair_edge;
    vector<Edge> maximum_match(int s, int t) {
        int res = 0;
        while (true) {
            visited.assign(node.size(), 0);
            int flow = update_residual_graph(s, t, INTMAX);
            if (flow == 0) break;
            res += flow;
        }
        for (auto&& e : node[s]) vertex_s.insert(e.to);
        for (auto&& e : node[t]) vertex_t.insert(e.to);
        for (auto&& v : vertex_s) {
            for (auto&& e : node[v]) {
                if (e.cap == 0 && e.to != s) {
                    matching_pair_edge.emplace_back(e);
                    break;
                }
            }
        }
        return matching_pair_edge;
    }

    // 最小辺被覆
    vector<Edge> edge_cover;
    vector<Edge> minumum_edge_cover(int s, int t){
        if (matching_pair_edge.size() == 0) maximum_match(s, t);
        copy(matching_pair_edge.begin(), matching_pair_edge.end(), back_inserter(edge_cover));
        set<int> _matching_node;
        for(auto&& e:matching_pair_edge){
            _matching_node.insert(e.from);
            _matching_node.insert(e.to);
        }
        for(auto&& v:vertex_s){
            if(_matching_node.find(v)==_matching_node.end()){
                edge_cover.emplace_back(node[v][0]);
            }
        }
        for(auto&& v:vertex_t){
            if(_matching_node.find(v)==_matching_node.end()){
                edge_cover.emplace_back(node[v][0]);
            }
        }
        return edge_cover;
    }


    // 最小点被覆
    set<int> vertex_cover;
    void update_vertex_cover_candidates(int v, int depth = 0) {
        visited[v] = 1;
        if (depth % 2 == 1)
            vertex_cover.insert(v);
        else
            vertex_cover.erase(v);
        for (auto&& e : node[v]) {
            if (visited[e.to] == 1 || e.cap == 0) continue;
            update_vertex_cover_candidates(e.to, depth + 1);
        }
    }
    
    
    set<int> mininum_vertex_cover(int s, int t) {
        if (matching_pair_edge.size() == 0) maximum_match(s, t);
        vertex_cover.clear();
        visited.assign(node.size(), 0);
        visited[s] = visited[t] = 1;
        for (auto&& e : matching_pair_edge) vertex_cover.insert(e.from);
        for (auto&& v : vertex_s) {
            if (vertex_cover.find(v) == vertex_cover.end()) update_vertex_cover_candidates(v);
        }
        return vertex_cover;
    }
    

    // 最大安定集合
    set<int> independent_set;
    set<int> maximum_independent_set(int s, int t) {
        independent_set.clear();
        set<int> mvc = mininum_vertex_cover(s, t);
        for (auto&& v : vertex_s)
            if (mvc.find(v) == mvc.end()) independent_set.insert(v);
        for (auto&& v : vertex_t)
            if (mvc.find(v) == mvc.end()) independent_set.insert(v);
        return independent_set;
    }

};

struct Bigraph2 {
    struct Edge {
        int rev, from, to, cap;
        Edge(int r, int f, int t, int c = 1) : rev(r), from(f), to(t), cap(c){};
    };
    int _n, _s, _t;
    vector<vector<Edge>> node;
    set<int> vertex_s, vertex_t;

    // Bigraph(int n, int s, int t): n(n), node(n), _s(s), _t(t){};
    Bigraph2(int n) : _n(n), node(n+2), _s(n), _t(n+1){};
    
    void init() {
        for(int i=0; i<_n; i++){
            if(node[i].size()==0)continue;
            if(node[i][0].cap>0) this->add_edge(_s, i);
            else this->add_edge(i, _t);
        }
    }

    void add_edge(int from, int to, int cap = 1) {
        int idx_from = node[from].size();
        int idx_to = node[to].size();
        node[from].emplace_back(idx_to, from, to, cap);
        node[to].emplace_back(idx_from, to, from, 0);
    }

    void run_flow(Edge& e, int f) {
        e.cap -= f;
        node[e.to][e.rev].cap += f;
    }

    int update_residual_graph(int v, int t, int f) {
        if (v == t) return f;
        visited[v] = 1;
        for (auto&& e : node[v]) {
            if (visited[e.to] == 1) continue;
            if (e.cap == 0) continue;
            int flow = update_residual_graph(e.to, t, min(f, e.cap));
            if (flow == 0) continue;
            run_flow(e, flow);
            return flow;
        }
        return 0;
    }

    vector<int> visited;
    vector<Edge> matching_pair_edge;
    vector<Edge> maximum_match() {
        init();
        int res = 0;
        while (true) {
            visited.assign(node.size(), 0);
            int flow = update_residual_graph(_s, _t, INTMAX);
            if (flow == 0) break;
            res += flow;
        }
        for (auto&& e : node[_s]) vertex_s.insert(e.to);
        for (auto&& e : node[_t]) vertex_t.insert(e.to);
        for (auto&& v : vertex_s) {
            for (auto&& e : node[v]) {
                if (e.cap == 0 && e.to != _s) {
                    matching_pair_edge.emplace_back(e);
                    break;
                }
            }
        }
        return matching_pair_edge;
    }

    // 最小辺被覆
    vector<Edge> edge_cover;
    vector<Edge> minumum_edge_cover() {
        if (matching_pair_edge.size() == 0) maximum_match();
        copy(matching_pair_edge.begin(), matching_pair_edge.end(), back_inserter(edge_cover));
        set<int> _matching_node;
        for (auto&& e : matching_pair_edge) {
            _matching_node.insert(e.from);
            _matching_node.insert(e.to);
        }
        for (auto&& v : vertex_s) {
            if (_matching_node.find(v) == _matching_node.end()) {
                edge_cover.emplace_back(node[v][0]);
            }
        }
        for (auto&& v : vertex_t) {
            if (_matching_node.find(v) == _matching_node.end()) {
                edge_cover.emplace_back(node[v][0]);
            }
        }
        return edge_cover;
    }

    // 最小点被覆
    set<int> vertex_cover;
    void update_vertex_cover_candidates(int v, int depth = 0) {
        visited[v] = 1;
        if (depth % 2 == 1)
            vertex_cover.insert(v);
        else
            vertex_cover.erase(v);
        for (auto&& e : node[v]) {
            if (visited[e.to] == 1 || e.cap == 0) continue;
            update_vertex_cover_candidates(e.to, depth + 1);
        }
    }

    set<int> mininum_vertex_cover() {
        if (matching_pair_edge.size() == 0) maximum_match();
        vertex_cover.clear();
        visited.assign(node.size(), 0);
        visited[_s] = visited[_t] = 1;
        for (auto&& e : matching_pair_edge) vertex_cover.insert(e.from);
        for (auto&& v : vertex_s) {
            if (vertex_cover.find(v) == vertex_cover.end()) update_vertex_cover_candidates(v);
        }
        return vertex_cover;
    }

    // 最大安定集合
    set<int> independent_set;
    set<int> maximum_independent_set() {
        independent_set.clear();
        set<int> mvc = mininum_vertex_cover();
        for (auto&& v : vertex_s)
            if (mvc.find(v) == mvc.end()) independent_set.insert(v);
        for (auto&& v : vertex_t)
            if (mvc.find(v) == mvc.end()) independent_set.insert(v);
        return independent_set;
    }
};


struct Solver {
    void solve() {
        int x, y, e;
        cin >> x >> y >> e;
        int n = x + y;
        Bigraph g(n + 2);
        rep(i, e) {
            int a, b;
            cin >> a >> b;
            b += x;
            g.add_edge(a, b);
        }
        rep(i, x) g.add_edge(n, i);
        rep(i, y) {
            g.add_edge(i + x, n + 1);
        }
        

        auto ans = g.maximum_match(n, n + 1);
        for (auto&& a : ans) {
            printf("%d:%d ", a.from, a.to);
        }
        cout << endl;
        auto S0 = g.minumum_edge_cover(n, n + 1);
        for (auto&& s : S0) {
            printf("%d:%d ", s.from, s.to);
        }
        cout << endl;
        set<int> S1 = g.mininum_vertex_cover(n, n + 1);
        for (auto&& s : S1) {
            printf("%d ", s);
        }
        cout << endl;
        set<int> S2 = g.maximum_independent_set(n, n+1);
        for (auto&& s : S2) {
            printf("%d ", s);
        }
        cout << endl;
    };
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
