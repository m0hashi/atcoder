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
#define rep2(i, k, n) for (decltype(n) i = k; i <= (n); i++)
#define repr(i, n) for (decltype(n) i = (n)-1; i >= 0; i--)
#define repr1(i, n) for (decltype(n) i = (n); i > 0; i--)
#define repr2(i, k, n) for (decltype(n) i = n; i >= k; i--)
auto chmax = [](auto& a, auto b) {bool ret=a<b; if(ret)a=b; return ret; };
auto chmin = [](auto& a, auto b) {bool ret=a>b; if(ret)a=b; return ret; };
template <typename T>
using pq_inv = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
struct BucketRangeMinimumQuery {
    int N, n_bucket, bucket_size;
    T e = (1LL << 31) - 1;
    // T e = 0;
    vector<T> array_raw;
    vector<T> array_q;
    vector<int> array_lazy;
    BucketRangeMinimumQuery(int n) : N(n) {
        n_bucket = floor(sqrt(N));
        bucket_size = (N + n_bucket - 1) / n_bucket;
        array_raw.assign(N, e);
        array_q.assign(n_bucket, 0);
        array_lazy.assign(n_bucket, 0);
    }
    int get_bucket_idx(int x) {
        return x / bucket_size;
    }
    pair<int, int> get_bucket_range(int bucket_idx) {
        int l = bucket_idx * bucket_size;
        int r = min(l + bucket_size - 1,N-1);
        return {l, r};
    }
    void lazy_load(int i, T x){
        array_q[i]=x;
        array_lazy[i]=1;
    }
    void lazy_unload(int i) {
        if(array_lazy[i]==0) return;
        auto [_l, _r] = get_bucket_range(i);
        for (int k = _l; k <= _r; k++) {
            array_raw[k] = array_q[i];
        }
        array_lazy[i]=0;
    }
    void range_update(int l, int r, T x) {
        int left_bucket = get_bucket_idx(l);
        int right_bucket = get_bucket_idx(r);
        for (int i = left_bucket; i <= right_bucket; i++) {
            if (i != left_bucket && i != right_bucket) {
                lazy_load(i, x);
            } else {
                lazy_unload(i);
                auto [_l, _r] = get_bucket_range(i);
                _l = max(_l, l);
                _r = min(_r, r);
                for (int j = _l; j <= _r; j++) {
                    array_raw[j] = x;
                }
            }
        }
    }
    T get(int i) {
        int b = get_bucket_idx(i);
        lazy_unload(b);
        return array_raw[i];
    }
};

// verify
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
struct Solver {
    void solve() {
        int n, q;
        cin >> n >> q;
        BucketRangeMinimumQuery<ll> b(n);
        rep(i, q) {
            int t;
            cin >> t;
            if (t == 0) {
                int l, r, x;
                cin >> l >> r >> x;
                // l--;
                // r--;
                b.range_update(l, r, x);
            } else {
                int x;
                cin >> x;
                // x--;
                ll out = b.get(x);
                cout << out << endl;
            }
        }
    };
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
