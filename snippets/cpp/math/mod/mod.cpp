// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>

#include <atcoder/all>
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
template <typename T> using pq_inv = priority_queue<T, vector<T>, greater<T>>;
vector<int> dd4={1, 0, -1, 0, 1};  // 4方位 rep(i,4) nh=h+dd4[i]; nw=w+dd4[i+1];
vector<int> dd8={1, 0, -1, 0, 1, 1,-1, -1, 1};  // 8方位 rep(i,8) nh=h+dd8[i]; nw=w+dd8[i+1];
using mint = atcoder::modint1000000007;

struct ModCom{
    int lim=1e7;
    vector<mint> X;
    void init(){
        X.resize(lim+1);
        X[0]=X[1]=1;
        for(int i=1; i<=lim; i++)X[i]=i*X[i-1];
    }
    mint calc(int n, int k){
        if(X.size()==0)init();
        return X[n]*X[k].inv()*X[n-k].inv();
    }
};


struct Solver {
    void solve(int case_id){
        
    };
};

int main() {
    std::cin.tie(nullptr);
    int T;
    // cin >> T;
    T=1;
    for(int i=0; i<T; i++){
        Solver solver;
        solver.solve(i);
    }
    return 0;
}
