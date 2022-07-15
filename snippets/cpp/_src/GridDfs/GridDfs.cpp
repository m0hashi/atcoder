#include <bits/stdc++.h>
using namespace std;


struct GridDfs {
    vector<int> dir_h = {0, 1, 0, -1};
    vector<int> dir_w = {1, 0, -1, 0};
    int H, W;
    int dfs(vector<string>& grid, pair<int, int> par, pair<int, int> cur, const pair<int, int>& dest, vector<vector<bool>>& state, int dist) {
        int ans = -1;
        state[cur.first][cur.second] = true;
        rep(dir, 4) {
            int hnex = cur.first + dir_h[dir];
            int wnex = cur.second + dir_w[dir];
            pair<int, int> nex = {hnex, wnex};
            if (nex == par) continue;
            if (nex == dest) {
                ans = max(ans, dist + 1);
            } else {
                if (hnex < 0 || wnex < 0 || hnex >= H || wnex >= W || grid[hnex][wnex]=='#') continue;
                if (state[hnex][wnex]) continue;
                ans = max(ans, dfs(grid, cur, nex, dest, state, dist+1));
            }
        }
        state[cur.first][cur.second] = false;
        return ans;
    }
    void solve() {
        cin >> H >> W;
        vector<string> grid(H);
        rep(i, H) cin >> grid[i];
        vector state = vector(H, vector<bool>(W));
        int ans = -1;
        rep(h, H) rep(w, W) {
            pair<int, int> par = {-1, -1};
            pair<int, int> cur = {h, w};
            if (grid[h][w]=='#') continue;
            ans = max(ans, dfs(grid, par, cur, cur, state, 0));
        }

        cout << ans << endl;
        return;
    };
};


int main(){
    return 0;
}
