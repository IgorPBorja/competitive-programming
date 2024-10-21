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

vector<int> zfunc(string& s){
	int l = 1, r = 0;
	const int n = s.size();
	vector<int> z(n);
	z[0] = n;
	for (int i = 1; i < n; i++){
		// s[i-l]...s[r-l] = s[i]...s[r] (I)
		// but if z[i-l] = k then also
		// s[0]...s[k-1] = s[i-l]...s[i-l+k-1]
		// so if k <= r-i then because of the maximality of z[i-l], s[0..k-1] = s[i...i+k-1] and s[k] != (s[i-l+k] = s[i+k])
        // where the equality follows from (I) since i+k <= r
		// which means we can't expand prefix/prefix pair and z[i] = z[i-l]
		// Otherwise, if k > r-i, this means s[0...r-i] == s[i-l...r-l] == s[i...r]
        // so we reset the interval from [l,r] to [i,r] and try to expand it
		if (i > r){
			// outside interval, reset to empty closed interval
			l = i;
			r = i - 1;
		}
		if (z[i - l] <= r - i){
			z[i] = z[i - l];
		} else {
            l = i;
			while (r + 1 < n && s[r + 1] == s[r + 1 - i]){
				++r;
			}
			z[i] = r - i + 1;
		}
	}
	return z;
}

void solve(){
    string s;
    cin >> s;
    // for each length (l) brute-force in O(n / l) ==> total O(n * sum 1/l) = O(n log n)
    const i64 n = s.size();
    vector<i64> periods;
    vector<int> z = zfunc(s);
    // printmsg("z=", z.begin(), z.end());
    for (i64 i = 1; i <= n; i++){
        // 0..i-1 + (offset * i)
        i64 ptr = i;
        bool ok = true;
        while (ptr < n){
            if (z[ptr] < min(i, n - ptr)){
                ok = false;
                break;
            }
            ptr += i;
        }
        if (ok) periods.emplace_back(i);
    }
    for (i64 x: periods){
        cout << x << " ";
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
