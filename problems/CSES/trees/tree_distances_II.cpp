// #define TESTCASES
// #define DEBUG
 
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
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 MAXN = 2e5;
i64 subtree_size[MAXN];
i64 depth[MAXN];
i64 sum_arr[MAXN];
vector<vector<i64>> tree(MAXN);

void sum(i64 u, const i64 n, i64 p = -1){
    if (p >= 0){
        sum_arr[u] = sum_arr[p] + n - (i64)2 * subtree_size[u];
    } else { // root
        sum_arr[u] = 0;
        for (i64 i = 0; i < n; i++){
            sum_arr[u] += depth[i];
        }
    }

    for (i64 v: tree[u]){
        if (v == p) continue;
        sum(v, n, u);
    }
}

void size(i64 u, i64 p = -1, i64 d = 0){
    subtree_size[u] = 1;
    depth[u] = d;
    for (i64 v: tree[u]){
        if (v == p) continue;
        size(v, u, d + 1);
        subtree_size[u] += subtree_size[v];
    }
}

void solve(){
    const i64 root = 0;

    i64 n;
    cin >> n;

    i64 a, b;
    for (i64 i = 0; i < n - 1; i++){
        cin >> a >> b;
        --a; --b;
        tree[a].emplace_back(b);
        tree[b].emplace_back(a);
    }

    size(root);
    sum(root, n);

    // printmsg("subtree_size=", subtree_size, subtree_size + n);
    // printmsg("up_sum=", sum_arr, sum_arr + n);

    for (i64 i = 0; i < n; i++){
        cout << sum_arr[i] << " ";
    }
    cout << endl;
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
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
