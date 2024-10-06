#define TESTCASES
 
#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

vector<i64> dp;
vector<vector<i64>> tree;
i64 maxc = 0;

void dfs(i64 u, i64 x, i64 parent){
    // the only subtree that risks going below x after cuts is the 0-subtree
    dp[u] = 1;
    for (i64 v: tree[u]){
        if (v == parent)
            continue;
        // go down the component and do the necessary cuts first
        dfs(v, x, u);
        
        // added v-subtree, already cut
        dp[u] += dp[v];

        // could cut (u,v) edge:
        if (dp[v] >= x){
            dp[u] -= dp[v];
            ++maxc;
        }
    }
}


void solve(){
    i64 n, k;
    cin >> n >> k;

    tree.resize(n); tree.assign(n, vector<i64>());
    dp.resize(n); dp.assign(n, 0);


    for (i64 i = 0; i < n - 1; i++){
        i64 a, b;
        cin >> a >> b;
        --a; --b;
        tree[a].emplace_back(b);
        tree[b].emplace_back(a);
    }

    i64 l = 1, r = n, ans = 1;
    while (l <= r){
        // reset
        maxc = 0;

        i64 x = l + (r - l) / 2;
        dfs(0, x, n);
        
        // made 0-subtree < x
        // suffices to merge one single cut back
        // (the most shallow one, that connects directly to the 0-subtree) -> the first one!
        // since it has size >=x
        if (dp[0] < x && maxc > 0){
            --maxc;
        }
        if (maxc >= k){
            ans = x;
            l = x + 1;
        } else {
            r = x - 1;
        }
    }
    cout << ans << endl;
}
 
signed main(){
	fastio;
    //freopen("in", "r", stdin);
	int t;
#ifdef TESTCASES
	cin >> t;
#else
	t = 1;
#endif
	while (t--){
		solve();
	}
}
