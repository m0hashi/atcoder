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

template <typename T>
struct ZobristHash {
    random_device seed;
    mt19937_64 engine;
    uniform_int_distribution<long long> randint;
    map<T, long long> hash_dict;
    ZobristHash(): engine(seed()), randint(0,1LL<<63) {}

    long long get_hash(const T key){
        if (hash_dict.find(key)==hash_dict.end()){
            hash_dict[key]=randint(engine);
        }
        return hash_dict[key];
    }
    
};

template <typename T>
struct ZobristHash_128 {
    random_device seed;
    mt19937_64 engine;
    uniform_int_distribution<long long> randint;
    map<T, __int128_t> hash_dict;
    ZobristHash(): engine(seed()), randint(0,1LL<<63) {}

    __int128_t get_hash(const T key){
        if (hash_dict.find(key)==hash_dict.end()){
            hash_dict[key]=(((__int128_t)randint(engine))<<63) + randint(engine);
        }
        return hash_dict[key];
    }
    
};

int main() {
    ZobristHash<pair<int,int>> zh;
    cout << zh.get_hash({1,2}) << endl;

}
