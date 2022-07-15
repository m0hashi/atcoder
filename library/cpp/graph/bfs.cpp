// #include<iostream>
// #include<algorithm>
#include <atcoder/all>
#include <fstream>
#include "bits/stdc++.h"
#define _GLIBCXX_DEBUG
using namespace std;

struct Pos{
    int x,y;
    Pos(int x, int y){
        this->x=x;
        this->y=y;
    }
};

struct Graph{
    vector<vector<char>> Mat;
    vector<vector<int>> dist;
    int R,C;
    Graph(int R,int C){
        this->R=R;
        this->C=C;
        Mat.assign(R,vector<char>(C));
        dist.assign(R,vector<int>(C,-1));
    }
    void bfs(int sx, int sy){
        queue<Pos> q;
        vector<vector<bool>> seen(R,vector<bool>(C,false));
        q.push(Pos(sx,sy));
        dist[sy][sx]=0;
        seen[sy][sx]=true;
        while(!q.empty()){
            Pos pos=q.front();
            q.pop();
            for(auto p:{Pos(pos.x+1,pos.y), Pos(pos.x-1, pos.y), Pos(pos.x, pos.y+1), Pos(pos.x, pos.y-1)}){
                if (p.x>=0 & p.x <C & p.y>=0 & p.y<R & seen[p.y][p.x]==false){
                    if(Mat[p.y][p.x]=='.') {
                        q.push(Pos(p.x, p.y));
                        dist[p.y][p.x]=dist[pos.y][pos.x]+1;
                    }else{
                        dist[p.y][p.x]=-1;
                    }
                        seen[p.y][p.x]=true;
                }
            }
        }
    }
};

int main(){
    cin.tie(0);
    string fname = "/workspaces/atc-env/work/tests/1.in";
    ifstream in(fname);
    cin.rdbuf(in.rdbuf());
    int R,C, sx, sy, gx, gy;
    cin >> R >> C >> sy >> sx >> gy >> gx;
    Graph G(R,C);
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin >> G.Mat[i][j];
        }
    }
    G.bfs(sx-1,sy-1);
    cout << G.dist[gy-1][gx-1] << endl;
    return 0;
}