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
    vector<i64> p;
    vector<i64> size;
    i64 max_size;
    i64 num_components;

    DSU(i64 n){
        p.resize(n);
        size.assign(n, 1);
        max_size = 1;
        num_components = n;
        for (i64 i = 0; i < n; i++) p[i] = i;
    }

    i64 get(i64 x){
        if (x != p[x]){
            p[x] = get(p[x]); // path compression
        }
        return p[x];
    }

    bool merge(i64 x, i64 y){
        i64 rx = get(x), ry = get(y);
        if (rx == ry){
            return false;
        }
        if (size[rx] > size[ry]){
            swap(rx, ry);
        }
        // merge x into y via their roots
        p[rx] = ry;
        size[ry] += size[rx];
        max_size = max(max_size, size[ry]);
        --num_components;
        return true;
    } 
};

void solve(){
    i64 n, m;
    i64 a, b;
    cin >> n >> m;

    DSU d(n);
    for (i64 i = 0; i < m; i++){
        cin >> a >> b;
        --a; --b; // 1-index to 0-index
        d.merge(a, b);
        cout << d.num_components << " " << d.max_size << endl;
    }
}
 
signed main(){
	fastio;
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
