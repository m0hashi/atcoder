#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MOD 1000000007
#define INF 1 << 30

template <typename U>
void pprint(vector<vector<U>> &X, int h, int w) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if(X[i][j]==INF){
                cout << '_' << ' ';
            }else{
                cout << X[i][j] << ' ';
            }
        }
        cout << endl;
    }
    cout << endl;
}

// https://atcoder.jp/contests/abc151/tasks/abc151_d
template <typename T>
class GridGraph {
   public:
    GridGraph(int h, int w, T cpath = '.', T cwall = '#') : _H(h), _W(w), _cpath(cpath), _cwall(cwall), A(h, vector<T>(w)) {}
    void add(int h, int w, T val) {
        A[h][w] = val;
    }
    bool is_wall(int h, int w) {
        return A[h][w] == _cwall;
    }
    int bfs(int sh, int sw) {
        assert(!is_wall(sh, sw));
        vector<vector<int>> dist(_H, vector<int>(_W, INF));
        vector<vector<bool>> seen(_H, vector<bool>(_W, false));
        queue<tuple<int, int, int>> q;
        q.push({sh, sw, 0});
        dist[sh][sw] = 0;
        seen[sh][sw] = true;
        while (!q.empty()) {
            auto [h, w, d] = q.front();
            q.pop();
            for (int dir = 0; dir < _ndir; dir++) {
                int nh = h + _dirh[dir];
                int nw = w + _dirw[dir];
                if (nh < 0 || nw < 0 || nh >= _H || nw >= _W) continue;
                // if (dist[nh][nw] != INF | A[nh][nw] == _cwall) continue;
                if (seen[nh][nw] | A[nh][nw] == _cwall) continue;
                seen[nh][nw] = true;
                dist[nh][nw] = d + 1;//隣接するセルを見た時点で距離が確定。訪問時に距離を確定させるとTLE
                q.push({nh, nw, d + 1});
            }
        }
        int ret = 0;
        for (auto d : dist)
            for (auto x : d)
                if (x != INF) ret = max(ret, x);
        return ret;
    }

   private:
    int _H, _W;
    vector<vector<T>> A;
    T _cpath;  // 通路
    T _cwall;  // 壁
    int _ndir = 4;
    vector<int> _dirh = {1, 0, -1, 0};
    vector<int> _dirw = {0, 1, 0, -1};
};

int main() {
    int H, W;
    cin >> H >> W;
    GridGraph<char> graph(H, W);
    for (int h = 0; h < H; h++) {
        string S;
        cin >> S;
        for (int w = 0; w < W; w++) {
            graph.add(h, w, S[w]);
        }
    }
    int ans = 0;
    for (int sh = 0; sh < H; sh++) {
        for (int sw = 0; sw < W; sw++) {
            if (graph.is_wall(sh, sw)) continue;
            ans = max(ans, graph.bfs(sh, sw));
        }
    }
    cout << ans << endl;

    return 0;
}