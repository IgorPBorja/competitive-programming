#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define endl '\n'
using namespace std;

void solve(){
    int n, s;
    cin >> n >> s;
    vector<vector<int>> pos(n + 1);

    int a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i];
    }
    pos[0].emplace_back(-1);
    // pref
    for (int i = 1; i < n; i++){
        a[i] += a[i - 1];
    }
    for (int i = 0; i < n; i++){
        pos[a[i]].emplace_back(i);
    }
    for (int i = 0; i <= n; i++){
        sort(pos[i].begin(), pos[i].end());
    }

    int ans = (int)2e9;
    for (int i = 0; i < n; i++){
        // remove i+1...n-1
        if (a[i] < s) continue;
        int j = upper_bound(pos[a[i] - s].begin(), pos[a[i] - s].end(), i) - pos[a[i] - s].begin() - 1;
        if (0 <= j && j < pos[a[i] - s].size()){
            int k = pos[a[i] - s][j];
            // remove 0...k
            ans = min(ans, k + 1 + (n - 1 - i));
        }
    }
    if (ans != (int)2e9){
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
}

int main(){
    fastio;
    int t;
    cin >> t;
    while (t--){
        solve();
    }
}