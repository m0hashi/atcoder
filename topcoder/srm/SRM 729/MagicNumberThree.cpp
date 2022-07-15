#include <algorithm>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
int MOD = 1e9 + 7;

typedef long long ll;
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define foreach(itr, c) for (__typeof(c.begin()) itr = c.begin(); itr != c.end(); itr++)

ll mod_pow(ll x, ll p, ll mod) {
    ll res = 1;
    while (p > 0) {
        if (p & 1) res = (res * x) % mod;
        x = (x * x) % mod;
        p >>= 1;
    }
    return res;
}

ll powll(ll x, ll p) {
    ll res = 1;
    while (p > 0) {
        if (p & 1) res = (res * x);
        x = (x * x);
        p >>= 1;
    }
    return res;
}

bool isOK(int bit) {
    int rem = 0;
    int count = 0;
    while (bit > 0) {
        rem += (count++ * bit % 3);
        bit /= 3;
    }
    return rem % 3 == 0;
}

class MagicNumberThree {
   public:
    int countSubsequences(string s) {
        int M = 451;
        for (auto &&x : s) x -= '0';

        vector<vector<int>> dp(s.size() + 1, vector<int>(M + 1));
        dp[0][0] = 1;
        for (int i = 1; i <= s.size(); i++) {
            for (int j = 0; j <= M; j++) {
                int k = s[i - 1];
                if (j - k >= 0) {
                    dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - k]) % MOD;
                } else {
                    dp[i][j] = (dp[i - 1][j]) % MOD;
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i <= M; i++)
            if (i % 3 == 0) ans = (ans + dp[s.size()][i]) % MOD;
        return ans - 1;
    }
};

// CUT begin
ifstream data("MagicNumberThree.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T>
void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string s, int __expected) {
    time_t startClock = clock();
    MagicNumberThree *instance = new MagicNumberThree();
    int __result = instance->countSubsequences(s);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!"
             << " (" << elapsed << " seconds)" << endl;
        return true;
    } else {
        cout << "FAILED!"
             << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        string s;
        from_stream(s);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if (do_test(s, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl
             << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1654512691;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 225 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "MagicNumberThree (225 Points)" << endl
             << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
