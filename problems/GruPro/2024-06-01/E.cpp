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

void solve(){
	string s;
	cin >> s;
	const i64 b = s.size();

	i64 digits[b];
	for (i64 i = 0; i < b; i++){
		digits[i] = s[i] - '0';
	}

	// try 3-digit solutions
	for (i64 i = 0; i < b; i++){
		for (i64 j = i + 1; j < b; j++){
			for (i64 k = j + 1; k < b; k++){
				if ((100 * digits[i] + 10 * digits[j] + digits[k]) % 8 == 0){
					cout << "YES" << endl;
					for (i64 l = 0; l <= i; l++) cout << digits[l];
					cout << digits[j];
					cout << digits[k] << endl;
					return;
				}
			}
		}
	}

	// try two digit solutions
	for (i64 i = 0; i < b; i++){
		for (i64 j = i + 1; j < b; j++){
			if ((10 * digits[i] + digits[j]) % 8 == 0){
				cout << "YES" << endl;
				cout << digits[i] << digits[j] << endl;
				return;
			}
		}
	}

	for (i64 i = 0; i < b; i++){
		if (digits[i] % 8 == 0){
			cout << "YES" << endl;
			cout << digits[i] << endl;
			return;
		}
	}

	cout << "NO" << endl;
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
