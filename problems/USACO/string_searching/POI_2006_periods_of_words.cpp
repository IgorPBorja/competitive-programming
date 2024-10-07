// https://szkopul.edu.pl/problemset/problem/k9UKIj11V6iPRc3LaiYQYHyi/site/?key=statement

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

vector<i64> kmp(const string &s){
    const i64 n = s.size();
    vector<i64> pi(n);
    pi[0] = 0;
    for (i64 i = 1; i < n; i++){
        i64 j = pi[i - 1];
        while (j > 0 && s[j] != s[i]){
            j = pi[j - 1];
        }
        if (s[j] == s[i]) ++j;
        pi[i] = j;
    }
    return pi;
}

void solve(){
    i64 k;
    string s;
    cin >> k;
    cin >> s;
    vector<i64> pi = kmp(s);
    
    i64 sum = 0;
    // find min{j > 0: j-prefix == j-suffix} for each i
    i64 min_pi[k];
    min_pi[0] = 1;
    for (i64 i = 1; i < k; i++){
        if (pi[i] > 0){
            min_pi[i] = min_pi[pi[i] - 1];
        } else {
            min_pi[i] = i + 1;
        }
    }
    for (i64 i = 0; i < k; i++){
        if (min_pi[i] <= (i + 1) / 2){
            // cout << "for prefix=" << s.substr(0, i + 1) << " we found period=" << s.substr(0, i + 1 - pi[i]) << endl;
            sum += i + 1 - min_pi[i];
        }
    }
    cout << sum << endl;
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
