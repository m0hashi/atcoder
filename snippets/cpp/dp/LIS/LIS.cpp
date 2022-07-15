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



vector<int> LISConstruction(vector<int>& A){
	vector<int>dp_val(A.size(),INTMAX);
	vector<int>len(A.size());
	rep(i,(int)A.size()){
		int loc = lower_bound(dp_val.begin(), dp_val.end(), A[i]) - dp_val.begin();
		dp_val[loc] = A[i];
		len[i] = loc+1; //Aiまでを利用してLISを構成したときの、Aiを末端とするLISの長さ
	}
    
    //LISを構成する末端の要素をみつけて逆順に構成していく
    vector<int> ret;
    int end_pos = max_element(len.begin(), len.end()) - len.begin(); // argmax(len). LISを構成したときのLIS末端要素のAにおけるインデックス
    int prev_len = len[end_pos];
    int prev_val = A[end_pos];
    for (int i = end_pos- 1; i >= 0; i--)
    {
        if(len[i]==prev_len-1  //末端からLIS末端の要素を確定させていくとき、末尾の要素が確定したLISより長さが1つ短いLISであり、かつその末端がAiであって
            && A[i]<prev_val){ // 要素が確定したLISの末端よりA_iが小さい場合
            ret.push_back(A[i]);
            prev_val=A[i];
            prev_len--;
        }
    }
    return ret;
}


int LIS(vector<int>& A){
	vector<int>dp(A.size(),INTMAX);
    // 各iを末端とするLISの構築
	vector<int>len(A.size());
	rep(i,(int)A.size()){
		int loc = lower_bound(dp.begin(), dp.end(), A[i]) - dp.begin();
		dp[loc] = A[i];
		len[i] = loc+1; //Aiまでを利用してLISを構成したときの、Aiを末端とするLISの長さ
	}
    return *max_element(len.begin(), len.end());

}

struct Solver{
    void solve(){
        vector<int> A={5,1,0,3,2,4,3,2,5,0};
        for(auto&& a:LISConstruction(A)){
            cout << a << ' ';
        }
        cout << endl;
    };
};

int main() {
    std::cin.tie(nullptr);
    Solver solver;
    solver.solve();
    return 0;
}

