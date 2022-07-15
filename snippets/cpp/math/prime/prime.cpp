// #define _GLIBCXX_DEBUG
#include <atcoder/all>

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
auto chmax = [](auto& a, auto b) {bool ret=a<b; if(ret)a=b; return ret;};
auto chmin = [](auto& a, auto b) {bool ret=a>b; if(ret)a=b; return ret;};
template<typename T> using pq_inv = priority_queue<T, vector<T>, greater<T>>;


vector<ll> sieveOfErathos(ll n){
    vector<int> isPrime(n+1,1);
    vector<ll> ret;
    isPrime[0]=isPrime[1]=0;
    for(ll p=2; p*p<=n; p++){
        if(!isPrime[p])continue;
        isPrime[p]=1;
        for(ll j=2*p; j<=n; j+=p) isPrime[j]=0;
    }
    for(int i=2; i<=n; i++) if(isPrime[i]) ret.push_back(i);
    return ret; 
}

vector<pair<ll,ll>> primeFactorize(ll n){
    vector<pair<ll,ll>> ret;
    ll div=2;
    while(div*div<=n){
        int count=0;
        while(n%div==0){
            n/=div;
            count++;
        }
        ret.push_back({div, count});
        div++;
    }
    if(n!=1) ret.push_back({n, 1});
    return ret;
}

struct Solver{
    void test_erathos(){
        for(auto&& x:sieveOfErathos(11)){
            cout << x << endl;
        }
    };
    void test_faotorize(){
        for(auto&& x:primeFactorize(12)){
            cout << x.first << ' ' << x.second <<  endl;
        }
    }
};
int main() {
    std::cin.tie(nullptr);
    Solver solver;
    // solver.test_erathos();
    solver.test_faotorize();
    return 0;
}
