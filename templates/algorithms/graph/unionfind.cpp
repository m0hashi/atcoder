#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class UnionFind {
   public:
    UnionFind(int n) : _par(n, -1), _siz(n, 1) {}
    bool is_same(int x, int y) {
        return root(x) == root(y);
    }
    bool merge(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        if (_siz[y] < _siz[x]) swap(x, y);
        _par[y] = x;
        _siz[x] += _siz[y];
        return true;
    }
    int size(int x) {
        return _siz[root(x)];
    }

   private:
    vector<int>
        _par,
        _siz;
    int root(int x) {
        if (_par[x] == -1)
            return x;
        else
            return _par[x] = root(_par[x]);  // union by rank
    }
};