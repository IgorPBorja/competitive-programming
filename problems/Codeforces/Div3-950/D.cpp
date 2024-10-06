#define TESTCASES
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

const i64 INF = 1e18;

void solve(){
	// removing a[i]
	// gcd(a[0], a[1]) <= ... <= gcd(a[i - 2], a[i - 1]) <= gcd(a[i - 1], a[i + 1]) <= gcd(a[i + 1], a[i + 2]) <= ...
	
	i64 n;
	cin >> n;
	i64 a[n], lgcd[n - 1], rgcd[n];
	for (i64 i = 0; i < n; i++){
		cin >> a[i];
	}

	for (i64 i = 0; i + 1 < n; i++){
		lgcd[i] = std::gcd(a[i], a[i + 1]);
		rgcd[i + 1] = lgcd[i];
	}

	bool pref[n], suf[n - 1];
	// pref[i]: rgcd[1], ..., rgcd[i] = gcd(a[i - 1], a[i])
	// suf[i]: lgcd[i], ..., lgcd[n - 2]
	pref[1] = true;
	suf[n - 2] = true;
	for (i64 i = 1; i < n - 2; i++){
		pref[i + 1] = pref[i] & (rgcd[i + 1] >= rgcd[i]);
		suf[n - 2 - i] = suf[n - 1 - i] & (lgcd[n - 2 - i] <= lgcd[n - 1 - i]);
	}
	// printmsg("a=", a, a + sizeof(a) / sizeof(i64));
	// printmsg("gcd=", gcd, gcd + sizeof(gcd) / sizeof(i64));
	// printmsg("pref=", pref, pref + sizeof(pref) / sizeof(bool));
	// printmsg("suf=", suf, suf + sizeof(suf) / sizeof(bool));
	
	bool ans = suf[1] | pref[n - 2];
	for (i64 i = 1; i < n - 1; i++){
		i64 g = std::gcd(a[i - 1], a[i + 1]);
		bool partial = true;
		partial &= (i - 1 >= 1) ? pref[i - 1] : true;
		partial &= (i + 1 <= n - 2) ? suf[i + 1] : true;
		partial &= g >= ((i - 1 >= 1) ? rgcd[i - 1] : -INF);
		partial &= g <= ((i + 1 <= n - 2) ? lgcd[i + 1] : +INF);
		ans = ans | partial;
	}
	if (ans){
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
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
