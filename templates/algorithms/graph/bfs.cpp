#include <bits/stdc++.h>
#include <fstream>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;

vector<int> bfs(vector<vector<int>> &G, int s) {
    vector<int> ret(G.size());
    vector<bool> seen(G.size());
    seen[s] = true;
    queue<P> todo; // {node, parent_node}
    todo.push({s, -1});
    while (!todo.empty()) {
        int u, p;
        tie(u, p) = todo.front();
        ret[u] = p;
        todo.pop();
        for (auto nu : G[u]) {
            if (seen[nu]) continue;
            todo.push({nu, u});
            seen[nu] = true;
        }
    }
    return ret;
}

class Graph{
    struct Edge{
        int w,to;
        Edge(int w,int to): w(w), to(to){}
    };

    private:
    public:
        vector<int> node;
        vector<vector<Edge>> edge;
        vector<int> order;
        vector<bool> seen;
        Graph(int N){
            node.resize(N,1);
            edge.resize(N);
        }
        void add_edge(int from, int to, int w=1){
            edge[from].push_back(Edge(w, to));
        }
        void set_node(int u, int val){
            node[u]=val;
        }
        void reset_order(){
            order.clear();
        }
        void dfs(int v=0, int d=0){
            seen[v]=true;
            order[v]=d;
            for(auto nv:edge[v]){
                if(seen[nv.to])continue;
                dfs(v, d+1);
            }
        }
};