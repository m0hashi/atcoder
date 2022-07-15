#include <bits/stdc++.h>
#include <fstream>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;

class Edge {
   public:
    int e, to;
    Edge(int e, int to) : e(e), to(to) {}
};
class Node {
   public:
    int val;
    Node(int val) : val(val) {}
};

class Graph {
   public:
    Graph(int n) : _n(n), _edge(n), _node(n) {}
    int size(){
        return _n;
    }
    void add_edge(int v, int e, int to) {
        assert(v >= 0 && v < _n);
        _edge[v].push_back({e, to});
    }
    vector<Edge> &get_edges(int v) {
        assert(v >= 0 && v < _n);
        return _edge[v];
    }
    void set_node(int v, int val){
        assert(v >= 0 && v < _n);
        _node[v]=val;
    }
    Node &get_node(int v){
        assert(v >= 0 && v < _n);
        return _node[v];
    }

   private:
    int _n;
    vector<vector<Edge>> _edge;
    vector<Node> _node;
};

int dfs(Graph &G, int s, int t){
    deque<P> todo;
    vector<bool> seen(G.size());
    vector<int> order(G.size()); // 訪問順　
    int ord_count=1;
    int depth=0;
    todo.push_back(P{s,depth});
    while(!todo.empty()){
        ll u,d;
        tie(u,d) = todo.back();
        order[u]=ord_count++;
        for(auto e:G.get_edges(u)){
            if(seen[e.to])continue;
            seen[e.to]=true;
            todo.push_back({e.to, d+1});
        }
    }
    return 1;
}
