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
struct BucketRangeSumQuery {
    int N, n_bucket, bucket_size;
    vector<T> array_n;
    vector<T> bucket_sum;
    BucketRangeSumQuery(int n) : N(n) {
        n_bucket = floor(sqrt(N));
        bucket_size = (N + n_bucket - 1) / n_bucket;
        array_n.assign(N, 0);
        bucket_sum.assign(n_bucket, 0);
    }
    int _bucket_idx(int x) {
        return x / bucket_size;
    }
    pair<int, int> _bucket_range(int bucket_idx) {
        int l = bucket_idx * bucket_size;
        int r = l + bucket_size - 1;
        return {l, r};
    }
    void add(int loc, int x) {
        array_n[loc] += x;

        int idx = _bucket_idx(loc);
        bucket_sum[idx] += x;
    }
    void update(int loc, int x) {
        int tmp = array_n[loc];
        array_n[loc] = x;

        int idx = _bucket_idx(loc);
        bucket_sum[idx] += x-tmp;
    }
    ll range_sum(int l, int r) {
        T ret = 0;
        int left_bucket = _bucket_idx(l);
        int right_bucket = _bucket_idx(r);
        for (int i = left_bucket; i <= right_bucket; i++) {
            if (i != left_bucket && i != right_bucket) {
                ret += bucket_sum[i];
            } else {
                auto [_l, _r] = _bucket_range(i);
                _l = max(l,_l);
                _r = min(r, _r);
                ret += accumulate(array_n.begin()+_l, array_n.begin()+_r+1, 0LL);
            }
        }
        return ret;
    }
};

//verify
//https://judge.u-aizu.ac.jp/onlinejudge/submission.jsp#submit/DSL_2_B
struct Solver {
    void solve(){
        int n,q;
        cin >> n >> q;
        BucketRangeSumQuery<ll> b(n);
        rep(i,q){
            int t,x,y;
            cin >> t >> x >> y;
            if(t==0){
                x--;
                b.add(x,y) ;
            }else{
                x--;y--;
                cout << b.range_sum(x,y) << endl;
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
