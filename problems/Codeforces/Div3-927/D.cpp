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

void solve(){
	i64 n;
	string c;
	char trump;
	map<char, vector<i64>> cards;
	
	cin >> n;
	cin >> c;
	trump = c[0];
	for (i64 i = 0; i < 2 * n; i++){
		cin >> c;
		cards[c[1]].eb(c[0] - '0');
	}
	for (auto[suit, _]: cards){
		sort(cards[suit].begin(), cards[suit].end());
	}

	vector<string> ans;
	vector<string> rem;
	for (auto[suit, _]: cards){
		if (suit == trump) continue;
		i64 i = 0;
		for (; i < cards[suit].size() - 1; i += 2){
			ans.eb(to_string(cards[suit][i]) + string(1, suit));
			ans.eb(to_string(cards[suit][i + 1]) + string(1, suit));
		}
		if (i < cards[suit].size()){
			rem.eb(to_string(cards[suit][i]) + string(1, suit));
		}
	}
	
	i64 i = 0;
	for (string s: rem){
		if (i == cards[trump].size()){
			cout << "IMPOSSIBLE" << endl;
			return;
		}
		ans.emplace_back(s);
		ans.emplace_back(to_string(cards[trump][i]) + string(1, trump));
		++i;
	}
	for (; i < cards[trump].size() - 1; i += 2){
		ans.emplace_back(to_string(cards[trump][i]) + string(1, trump));
		ans.emplace_back(to_string(cards[trump][i + 1]) + string(1, trump));
	}
	for (i64 i = 0; i < ans.size() - 1; i += 2){
		cout << ans[i] << " " << ans[i + 1] << endl;
	}
}
 
signed main(){
	fastio;
	int t;
	freopen("/tmp/in", "r", stdin);
#ifdef TESTCASES
	cin >> t;
#else
	t = 1;
#endif
	while (t--){
		solve();
	}
}
