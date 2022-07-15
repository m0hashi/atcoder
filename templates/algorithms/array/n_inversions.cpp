#include "atcoder/all"
#include "bits/stdc++.h"
using namespace std;
#define ll long long
using mint = atcoder::modint1000000007;
using tpl = tuple<ll, ll, ll>;
using P = pair<ll, ll>;

int n_inversions(vector<int> &A) {
    int N = A.size();
    vector<pair<int, int>> X(N);
    vector<int> B(N);
    for (int i = 0; i < N; ++i) X[i] = {A[i], i};
    sort(X.begin(), X.end());
    for (int i = 0; i < N; ++i) B[X[i].second] = i;
    atcoder::fenwick_tree<int> bit(N);
    int ret=0;
    for(int i=0; i<N; ++i){
        ret += bit.sum(B[i]+1,N) ;
        bit.add(B[i],1);
    }
    return ret;

}