#include <bits/stdc++.h>
#define ll long long
#define rep(i,n) for(int i=0; i<n; i++)
#define rep1(i,n) for(int i=1; i<=n; i++)
using namespace std;



// N以下の数の個数を桁DPで求める
void solve1(){
    string S="3210" ;
    int N=S.size();
    vector<vector<int>> dp(S.size()+1,vector<int>(2));
    dp[0][0]=1;
    for(int i=0; i<N; i++){
        int D=S[i]-'0';
        for(int j=0; j<2; j++){
            for(int d=0; d<=(j?9:D); d++){
                dp[i+1][j || (d<D)] += dp[i][j];
            }
        }
    }
    cout << dp[N][0] + dp[N][1]<< endl;
}

// 2進数表記でS以下の数を桁DPで求める
void solve2(){
    string S = "100110";
    int N = S.size();
    vector<vector<ll>> dp(N+1, vector<ll>(2));
    dp[0][0]=1;
    for(int i=0; i<N; i++){
        int D = S[i]-'0';
        for(int j=0; j<2; j++){
            for(int d=0; d<=(j?1:D); d++){
                dp[i+1][j || d<D] += dp[i][j];
            }
        }
    }
    cout << dp[N][0] + dp[N][1] << endl;

}

//2進数表記でMを超えないもの
void solve3(){
    int M=38; //100110
    int K=0;
    while((M>>K)>0)K++;
    vector<vector<int>> dp(K+1, vector<int>(2));
    dp[0][0]=1;
    for(int i=0; i<K; i++){
        int D = ((M>>(K-1-i))&1);
        for(int j=0; j<2; j++){
            for(int d=0; d<=(j?1:D); d++){
                dp[i+1][j || d<D]+=dp[i][j];
            }
        }
    }
    cout << dp[K][1] + dp[K][0] << endl;
}

//2進数表記でxけたであってMを超えないもの

int main() {
    // solve3();
    vector<int> X(10), Y(10);
    int M=39;
    for(int i=0; i<=M; i++){
        int k=0;
        while((i>>k)>0)k++;
        X[k]++;
    }
    for(int i=1; i<10; i++){
        if(1<<(i) <=M ){
            Y[i]=(1<<(i-1));
        }else{
            Y[i] = (M+1) - (1<<(i-1));
            break;
        }
    }
    for(int i=0; i<10; i++) cout << i << ' ' << X[i] << ' ' << Y[i] << endl;
    
}