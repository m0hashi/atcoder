#include <bits/stdc++.h>
#define ll long long
using namespace std;

// https://atcoder.jp/contests/practice2/tasks/practice2_b #動作検証
// https://atcoder.jp/contests/arc033/tasks/arc033_3 #i番目に小さい数

template <typename T>
class BIT {
   public:
    BIT(int n) : _n(n), data(n, 0) {}
    void add(int p, T x) {
        assert(p >= 0 && p < _n);
        p++;
        for (int idx = p; idx <= _n; idx += (idx & -idx)) {
            data[idx - 1] += x;
        }
    }
    T sum(int l, int r) {
        assert(l >= 0 && l <= r && r <= _n);
        return sum(r) - sum(l);
    }
    T get(int p){
        return sum(p+1) - sum(p);
    }
    int lower_bound(T w) {
        if (w <= 0) return 0;
        int r = 1, x = 0;
        while (r < _n) r = r << 1;
        for (int len = r; len > 0; len = len >> 1) {
            if (x + len - 1 < _n && data[x + len - 1] < w) {
                w -= data[x + len - 1];
                x += len;
            }
        }
        return x;
    }

   private:
    int _n;
    vector<T> data;
    T sum(int r) {
        T ret = 0;
        for (int idx = r; idx > 0; idx -= (idx & -idx)) {
            ret += data[idx - 1];
        }
        return ret;
    }
};

int main() {
    int Q;
    cin >> Q;
    BIT<ll> bit(200010);
    for (int i = 0; i < Q; i++)
    {
        int t,x;
        cin >> t >> x;
        if(t==1){
            bit.add(x,1);
        }else{
            int idx=bit.lower_bound(x);
            cout << idx << endl;
            bit.add(idx,-1);
        }
    }
    return 0;
}
