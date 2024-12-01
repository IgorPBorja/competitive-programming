#define USING_TESTCASES
#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define i64 int64_t

using namespace std;

const i64 n = 32;

void solve(){
    i64 x;
    cin >> x;
    
    i64 ans = 0;
    vector<i64> path;
    i64 i = n - 1;
    vector<i64> path(n + 1, 0);
    for (i64 i = 0; i < n; i++){
        // since x < 2^30 this will never hit exactly at n-1 so we are fine
        if (!(ans & (1ll << i))){
            continue;
        }
        // we need to add 2^i
        if (path[i] == -1){
            path[i] = 0;
        } else if (path[i] == 1){
            path[i] = 0;
            path[i + 1] = 1;
        } else if (path[i] == 0 && i > 0 && path[i - 1] == 1){
            // 2^{i - 1} 0 0 ==> -2^{i-1} 0 2^{i+1}
            // add a total of 2^i to the sum
            path[i - 1] = -1;
            path[i + 1] = 1;
        } else if (path[i] == 0 && i > 0 && path[i - 1] == 1){
            // -2^{i-1} 0 0 ==> 2^{i - 1} 0 0
            // adds a total of 2^î to the sum
            path[i - 1] = 1;
        } else {
            // free way
            path[i] = 1;
        }
    }
    while (!path.empty() && path.back() == 0) path.pop_back();
    cout << path.size() << endl;
    for (i64 x: path) cout << x << " ";
    cout << endl;
}


signed main(){
    fastio;
    int t = 1;
#ifdef USING_TESTCASES
    cin >> t;
#endif
    while(t--) solve();
}