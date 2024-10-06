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

/*
   s[n] = sum(i=1...n)(1 + v10[i])

   1 * n + (2 * n/10 - 1 * n/10) + ...
   = sum n/10^k
   so we can do shift and carry
*/

string carry_sum(string &digits){
    const i64 n = digits.size();
    vector<i64> pref(n + 1);
    pref[0] = 0;
    for (i64 i = 0; i < n; i++){
        pref[i + 1] = pref[i] + (digits[i] - '0');
    }

    // reverse digits
    vector<char> s;
    i64 carry = 0;
    for (i64 i = 0; i < n; i++){
        // sum i-th digit (right-to-left) of n, n/10, ..., n/10^k
        // ==> d(n - 1 - i) + d(n - 2 - i) + ... + d(0)
        // = pref[n - 1 - i]
        carry += pref[n - i];
        s.emplace_back((carry % 10) + '0');
        carry /= 10;
    }
    while (carry > 0){
        s.emplace_back((carry % 10) + '0');
        carry /= 10;
    }
    while (s.size() > 1 && s.back() == '0'){
        s.pop_back();
    }
    reverse(s.begin(), s.end());
    const string t(s.begin(), s.end());
    return t;
}

void solve(){
    i64 n;
    cin >> n;
    string digits;
    cin >> digits;
    cout << carry_sum(digits) << endl;
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
