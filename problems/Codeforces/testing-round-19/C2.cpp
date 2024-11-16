// #define TESTCASES
 
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << setw(2) << *it << "|";} cout << endl;
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

vector<int> zfunc(const string& s){
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    // [l, r] is the largest interval that repeats as a prefix
    // so z[l] = r - l + 1
    int l = 1, r = 0;
    for (int i = 1; i < n; i++){
        if (i > r){
            r = i - 1;
            z[i] = 0;
        } else {
            // i..r repeats at i-l...r-l
            // we need to check if this repeats at the start
            // reuse repeating part
            z[i] = min(z[i - l], r - i + 1);
        }
        // try to expand (now anchored in i)
        while (r + 1 < n && s[r + 1 - i] == s[r + 1]){
            l = i;
            ++r;
            ++z[i];
        }
        // cerr << "z[" << i << "]=" << z[i] << " l=" << l << " r=" << r << endl;
    }
    return z;
}

void solve(){
    string s;
    cin >> s;
    const int n = s.size();
    vector<int> z = zfunc(s);
    // printmsg("s=", s.begin(), s.end());
    // printmsg("z=", z.begin(), z.end());
    // if i is a start of the merging segment
    // we must have s[0..n-1-i] = s[i...n-1]
    // s[i..n-1-i] is the common part
    for (int i = 1; i < n - i; i++){
        if (z[i] == n - i){  // s[0..n-1-i] = s[i...n-1]
            cout << "YES" << endl;
            for (int j = 0; j <= n - 1 - i; j++){
                cout << s[j];
            }
            cout << endl;
            return;
        }
    }
    cout << "NO" << endl;
}
 
signed main(){
	fastio;
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
