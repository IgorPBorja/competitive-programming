//LINK:
//https://usaco.org/index.php?page=viewproblem2&cpid=646

//#define TESTCASES

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

struct DSU{
    vector<i64> p, size;
    i64 num_components;

    DSU(i64 n){
        p.resize(n);
        size.assign(n, 1);
        num_components = 0;
        for (i64 i = 0; i < n; i++) p[i] = i;
    }

    // get root for element x
    i64 get(i64 x){
        if (x != p[x]){
            p[x] = get(p[x]); // path compression
        }
        return p[x];
    }

    // merge elements x and y
    bool merge(i64 x, i64 y){
        i64 rx = get(x), ry = get(y);
        // now we deal with the roots only
        if (rx == ry){
            return false;
        }

        if (size[rx] > size[ry]){
            swap(rx, ry);
        }
        // rx -> ry
        p[rx] = ry;
        size[ry] += size[rx];
        --num_components;
        return true;
    }

    bool is_connected(){
        return num_components == 1;
    }
};

void solve(){
    // we solve the problem in reverse
    i64 n, m;
    i64 a, b;
    vector<set<i64>> adj;
    vector<bool> vis;

    cin >> n >> m;
    adj.resize(n);
    vis.assign(n, false);

    for (i64 i = 0; i < m; i++){
        cin >> a >> b;
        --a; --b; // 1-index to 0-index
        adj[a].insert(b);
        adj[b].insert(a); // so it guarantees both adding a and adding b works
    }

    vector<i64> queries(n);
    vector<bool> answer(n);
    for (i64 i = 0; i < n; i++){
        cin >> queries[i];
        --queries[i]; // 1-index to 0-index
    }

    DSU d(n);

    for (i64 i = n - 1; i >= 0; i--){
        // add queries[i]: starts isolated
        ++d.num_components;
        // O(m) merges --> O(m alpha(n))
        vis[queries[i]] = true;
        for (i64 u: adj[queries[i]]){
            if (vis[u]) // merge only visited vertices
                d.merge(queries[i], u);
        }
        answer[i] = d.is_connected();
    }

    for (bool ans: answer){
        if (ans){
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
 
signed main(){
	fastio;
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
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
