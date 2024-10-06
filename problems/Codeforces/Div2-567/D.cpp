// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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



void solve(){
	i64 m, n, q;
	cin >> m >> n >> q;

	vector<pair<i64, i64>> c(n);  // cnts
	for (i64 i = 0; i < n; i++){
		c[i] = make_pair(0, i);
	}
	for (i64 i = 0; i < m; i++){
		i64 x;
		cin >> x;
		++c[x - 1].first;  // -1 for 0-indexing
	}
	
	sort(c.begin(), c.end());

	vector<i64> diffs(n);
	diffs[0] = 0;
	for (i64 i = 1; i < n; i++){
		// how much, given cnt'[0..i-1] equal to cnt[i-1], to make cnt'[0..i] equal to cnt[i]
		diffs[i] = i * (c[i].first - c[i - 1].first);
		// increment previous diffs
		diffs[i] += diffs[i - 1];
	}

	vector<pair<i64, i64>> queries(q);
	vector<i64> ans(q);
	Tree<i64> ordered_set;
      	i64 sz = 0;

	for (i64 i = 0; i < q; i++){
		cin >> queries[i].first;
		--queries[i].first;
		queries[i].second = i;
	}
	sort(queries.begin(), queries.end());

	for (i64 i = 0; i < q; i++){
		// desconsider the first m days (we already now the answer)
		queries[i].first -= m;
		i64 k = upper_bound(diffs.begin(), diffs.end(), queries[i].first) - diffs.begin() - 1;
		queries[i].first -= diffs[k];
		queries[i].first = queries[i].first % (k + 1);
		// now we know the first k + 1 are equal and the first k + 2 will never be equal, and we want to know which has some idx
		while (sz < k + 1){
			ordered_set.insert(c[sz].second);
			sz++;
		}
		ans[queries[i].second] = *ordered_set.find_by_order(queries[i].first);
	}

	for (i64 i = 0; i < q; i++){
		cout << ans[i] + 1 << endl;
	}
	
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
