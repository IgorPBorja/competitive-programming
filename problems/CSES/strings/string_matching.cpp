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

int kmp_search(string& p, string& t){
    const int n = p.size() + t.size() + 1;
    int substr_cnt = 0;
    int pi[n];
    pi[0] = 0;
    for (int i = 1; i < p.size(); i++){
        int j = pi[i - 1];  // amount of common chars
        // can expand prefix?
        while (j > 0 && p[j] != p[i]){
            j = pi[j - 1];
        }
        if (p[j] == p[i]){
            // extend by 1
            ++j;
        }
        pi[i] = j;
    }
    pi[p.size()] = 0;
    for (int i = 0; i < t.size(); i++){
        int j = pi[p.size() + i];  // amount of common chars
        // can expand prefix?
        while (j > 0 && (j == p.size() || p[j] != t[i])){
            // can't expand beyond p.size() because of sentinel, and can't expand without matching
            j = pi[j - 1];
        }
        if (p[j] == t[i]){
            // extend by 1
            ++j;
        }
        pi[p.size() + i + 1] = j;
        if (j == p.size()){
            ++substr_cnt;
        }
    }
    return substr_cnt;
}

void solve(){
    string t, p;
    cin >> t >> p;
    cout << kmp_search(p, t) << endl;
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
