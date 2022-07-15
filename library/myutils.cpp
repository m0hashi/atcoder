#include <atcoder/all>
#include "bits/stdc++.h"
#define _GLIBCXX_DEBUG
using namespace std;


template <typename T>
int n_inversions(vector<T> &A){
    int N=A.size();
    vector<pair<T,int>> X(N);
    for(int i=0; i<N; ++i){
        X[i]={A[i],i} ;
    }
    sort(X.begin(), X.end());
    vector<int > B(N);
    for(int i=0; i<N; ++i){
        B[X[i].second]=i;
    }
    atcoder::fenwick_tree<T> ft(N);
    ll ret=0;
    for(int i=0; i<N; ++i){
        ret+=i-ft.sum(0,B[i]+1) ;
        ft.add(B[i],1);
    }
    return ret;
}