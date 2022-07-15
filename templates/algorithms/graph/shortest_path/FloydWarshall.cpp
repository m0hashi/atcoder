#include <bits/stdc++.h>

#include <fstream>
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
#define INF 1ll<<50

class FloydWarshall {
   public:
    FloydWarshall(int n) : _n(n), edge(n), dist(n, vector<ll>(n, INF)) {
        for (int i = 0; i < n; i++) dist[i][i] = 0;
    }
    void add_edge(int v, int to, int w) {
        edge[v].push_back({w, to});
        dist[v][to] = w;
    }
    vector<vector<ll>> run() {
        for (int k = 0; k < _n; k++) {
            for (int i = 0; i < _n; i++) {
                for (int j = 0; j < _n; j++) {
                    if(dist[i][k]==INF||dist[k][j]==INF)continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        return dist;
    }

   private:
    int _n;
    ll _INF = 1 << 30;
    struct Edge {
        int w, to;
        Edge(int w, int to) : w(w), to(to) {}
        bool operator>(const Edge& rhs) const { return w > rhs.w; }
        bool operator<(const Edge& rhs) const { return w < rhs.w; }
    };
    vector<vector<Edge>> edge;
    vector<vector<ll>> dist;
};

// https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_C
int main() {
    int v, e;
    cin >> v >> e ;
    FloydWarshall fw(v);
    for (int i = 0; i < e; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        fw.add_edge(s, t, d);
    }
    auto dist = fw.run();
    bool has_negative_cycle = false;
    for (int i = 0; i < v; i++)
        if (dist[i][i] < 0) has_negative_cycle = true;
    if (has_negative_cycle) {
        cout << "NEGATIVE CYCLE" << endl;
        return 0;
    }
    for (int i = 0; i < v; i++) {
        for (int j = 0; j < v; j++) {
            if(j) cout << ' ';
            if (dist[i][j] >= INF) {
                cout << "INF";
            } else {
                cout << dist[i][j];
            }
        }
        cout << endl;
    }

    return 0;
}