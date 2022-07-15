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
void print(vector<T>& X) {
    for (auto&& a : X) {
        printf("%*lld ", 10, (ll)a);
    }
    cout << endl;
}
template <typename T>
struct SqrtDecomposition {
    int N, n_bucket, bucket_size;
    T e = (1LL << 31) - 1;
    // T e = 0;
    vector<T> array_raw;
    vector<T> bucket_store;
    vector<T> bucket_op;
    vector<T> bucket_lazy;
    vector<int> bucket_isloaded;
    SqrtDecomposition(int n) : N(n) {
        n_bucket = floor(sqrt(N));
        bucket_size = (N + n_bucket - 1) / n_bucket;
        array_raw.assign(N, e);
        bucket_store.assign(n_bucket, e);
        // bucket_op.assign(n_bucket, e);
        bucket_lazy.assign(n_bucket, e);
        bucket_isloaded.assign(n_bucket, 0);
    }
    int get_bucket_idx(const int& x) {
        return x / bucket_size;
    }
    pair<int, int> get_bucket_range(const int& bucket_idx) {
        int _l = bucket_idx * bucket_size;
        int _r = min(_l + bucket_size - 1, N - 1);
        return {_l, _r};
    }
    pair<int, int> get_bucket_range(const int& bucket_idx, const int& l, const int& r) {
        int _l = bucket_idx * bucket_size;
        int _r = min(_l + bucket_size - 1, N - 1);
        return {max(_l, l), min(_r, r)};
    }
    void lazy_load(const int& i, const T& x) {
        bucket_lazy[i] = x;
        bucket_isloaded[i] = 1;
    }
    bool lazy_unload(const int& i) {
        if (bucket_isloaded[i] == 0) return false;
        auto [_l, _r] = get_bucket_range(i);
        for (int k = _l; k <= _r; k++) {
            array_raw[k] = bucket_lazy[i];
        }
        bucket_isloaded[i] = 0;
        return true;
    }
    // void range_add(int l, int r, T x){
    //     int left_bucket = get_bucket_idx(l);
    //     int right_bucket = get_bucket_idx(r);
    //     for (int i = left_bucket; i <= right_bucket; i++){
    //         if(i!=left_bucket && i!=right_bucket){
    //             bucket_op[i] += x;
    //         }else{
    //             auto [_l, _r] = get_bucket_range(i, l, r);
    //             for (int k = _l; k <= _r; k++){
    //                 array_raw[k] += x;
    //                 bucket_store[i] += x;
    //             }
    //         }
    //     }
    // }
    void range_update(const int& l, const int& r, const T& x) {
        int left_bucket = get_bucket_idx(l);
        int right_bucket = get_bucket_idx(r);
        for (int i = left_bucket; i <= right_bucket; i++) {
            if (i != left_bucket && i != right_bucket) {
                lazy_load(i, x);
                bucket_store[i] = x;
            } else {
                lazy_unload(i);
                auto [_l, _r] = get_bucket_range(i, l, r);
                _l = max(_l, l);
                _r = min(_r, r);
                for (int j = _l; j <= _r; j++){
                    array_raw[j] = x;
                }
                tie(_l, _r) = get_bucket_range(i);
                bucket_store[i] = *min_element(array_raw.begin() + _l, array_raw.begin() + _r + 1);
            }
        }
    }
    T range_min(int l, int r) {
        int lb = get_bucket_idx(l);
        int rb = get_bucket_idx(r);
        T ret = e;
        for (int i = lb; i <= rb; i++) {
            if (i != lb && i != rb) {
                ret = min(ret, bucket_store[i]);
            } else {
                lazy_unload(i);
                auto [_l, _r] = get_bucket_range(i, l, r);
                for (int k = _l; k <= _r; k++) {
                    ret = min(ret, array_raw[k]);
                }
            }
        }
        return ret;
    }
};

// verify
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F&lang=ja
struct Solver {
    void solve() {
        int n, q;
        cin >> n >> q;
        SqrtDecomposition<ll> b(n);
        vector<int> idx(n);
        rep(i,n) idx[i]=i;
        rep(i, q) {
            int t;
            cin >> t;
            if (t == 0) {
                int l, r, x;
                cin >> l >> r >> x;
                // printf("(query(%d)) %d %d %d\n", i, l, r, x);
                // print(b.bucket_isloaded);
                // print(b.bucket_lazy);
                // print(b.bucket_store);
                // print(idx);
                // print(b.array_raw);
                // cout << "     ---------------------------------------------------------------------------" << endl;
                b.range_update(l, r, x);
                // print(b.bucket_isloaded);
                // print(b.bucket_lazy);
                // print(b.bucket_store);
                // print(idx);
                // print(b.array_raw);
            } else {
                int l, r;
                cin >> l >> r;
                // printf("(query:(%d)) %d %d\n", i, l, r);
                // print(b.bucket_isloaded);
                // print(b.bucket_lazy);
                // print(b.bucket_store);
                // print(idx);
                // print(b.array_raw);
                // cout << "     ---------------------------------------------------------------------------" << endl;
                ll out = b.range_min(l, r);
                // print(b.bucket_isloaded);
                // print(b.bucket_lazy);
                // print(b.bucket_store);
                // print(idx);
                // print(b.array_raw);
                // printf("(out) ");
                cout << out << endl;
            }
            // cout << "--------------------------------------------------------------------------------" << endl;
        }
    };
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}
