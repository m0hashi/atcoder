#include <iostream>
#include "bits/stdc++.h"
using namespace std;

int main() {
    vector<int> A = {1,2,4,6};
    int lb = lower_bound(A.begin(), A.end(), 4) - A.begin();
    int ub = upper_bound(A.begin(), A.end(), 4) - A.begin();
    cout << lb << endl;
    cout << ub << endl;
    return 0;
}