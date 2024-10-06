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
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
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

void solve(){
  string s;
  i64 m;
  cin >> s >> m;

  // for using the i-th character E as the first E character
  // for starting at position j (j <= i) we can use k (0 <= k <= m - (i - j + 1)) positions after p[i]
  // we have sum(j=max(p[i-1]+1, p[i]-m+1)...p[i]) (m - (p[i]- j + 1)) = (m - p[i]- 1) * min(m, p[i] - p[i-1]) + S(max(p[i-1]+1, p[i]-m+1), p[i])

  vector<i64> epos;
  epos.emplace_back(0);
  for (u64 i = 0; i < s.size(); i++){
    if (s[i] == 'E'){
      epos.emplace_back(i + 1);
    }
  }
  epos[0] = -(s.size() - epos.back());

  // printmsg("epos=", epos.begin(), epos.end());

  i64 ans = 0;
  auto sum_ap = [](i64 a, i64 b){
    return ((b * (b + 1)) / 2) - ((a - 1) * a) / 2;
  };
  for (u64 i = 1; i < epos.size(); i++){
  	const i64 start = max(epos[i - 1] + 1, epos[i] - m + 1);
  	ans += sum_ap(m - (epos[i] - start), m);
  	// cout << "ans=" << ans << endl;
  }
  cout << ans << endl;
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
