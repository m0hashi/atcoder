#include <bits/stdc++.h>
using namespace std;

struct MaximumFlowFoldFulkerson {
    int INTMAX=std::numeric_limits<int>::max();
    struct Edge {
        int rev, from, to, cap;
        Edge(int r, int f, int t, int c = 1) : rev(r), from(f), to(t), cap(c) {}
    };
    vector<vector<Edge>> node;
    vector<int> visited;
    MaximumFlowFoldFulkerson(int n): node(n){}

    size_t size() {
        return node.size();
    }

    Edge& redge(Edge& e) {
        return node[e.to][e.rev];
    }
    void run_flow(Edge& e, int flow) {
        e.cap -= flow;
        redge(e).cap += flow;
    }

    void add_edge(int from, int to, int cap) {
        int idx_from = (int)node[from].size();
        int idx_to = (int)node[to].size();
        node[from].emplace_back(idx_to, from, to, cap);
        node[to].emplace_back(idx_from, to, from, 0);
    }
    
    
    int foldfs(int v, int t, int f){
        if(v==t) return f;
        visited[v]=1;
        for(auto& e:node[v]){
            if(visited[e.to]==1)continue;
            if(e.cap==0)continue;
            int flow = foldfs(e.to, t, min(f, e.cap));
            if(flow==0)continue;
            run_flow(e,flow);
            return flow;
        }
        return 0;
    }

    int solve(int s, int t){
        int res=0;
        while(true){
            visited.assign(node.size(),0);
            int flow=foldfs(s,t,INTMAX);
            if (flow==0) return res;
            res+=flow;
        }
        return 0;
    }

};

int main() {
    int v,e;
    cin >> v >> e;
    MaximumFlowFoldFulkerson f(v);
    for (int i = 0; i < e; i++)
    {
        int u,v,c;
        cin >> u >> v >> c;
        f.add_edge(u,v,c);
    }
    cout << f.solve(0,v-1) << endl;
    
    return 0;
}
