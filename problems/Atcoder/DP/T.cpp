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

const i64 MOD = (i64)1e9 + 7;

void solve(){
    i64 n;
    cin >> n;
    string s;
    cin >> s;

    // NOTE: T[i][x] = quantidade de permutações de (0,...,i) terminando em x
    // pt[i][x] := sum(0 <= y <= x) T[i][x]
    // st[i][x] := sum(x <= y <= i) T[i][x]

    i64 pt[n][n], st[n][n];
    pt[0][0] = 1;
    st[0][0] = 1;
    for (i64 i = 0; i < n - 1; i++){
        if (s[i] == '<'){
            // can't end in 0
            pt[i + 1][0] = 0;
            for (i64 x = 1; x <= i + 1; x++){
                pt[i + 1][x] = (pt[i + 1][x - 1] + pt[i][x - 1]) % MOD;
            }

            // ST[i + 1][i + 1] = T[i + 1][i + 1] = sum T[i][j] = ST[i][0]
            st[i + 1][i + 1] = st[i][0];
            for (i64 x = i; x > 0; x--){
                st[i + 1][x] = (st[i + 1][x + 1] + pt[i][x - 1]) % MOD;
            }
            // can't end in 0 so suffix sum do not change
            st[i + 1][0] = st[i + 1][1];  
        } else if (s[i] == '>'){
            // PT[i + 1][0] = T[i + 1][0] = sum T[i][j] = PT[i][i]
            pt[i + 1][0] = pt[i][i];
            
            for (i64 x = 1; x <= i; x++){
                pt[i + 1][x] = (pt[i + 1][x - 1] + st[i][x]) % MOD;
            }
            // can't end in i + 1 so prefix sum does not change
            pt[i + 1][i + 1] = pt[i + 1][i];

            // can't end in i + 1
            st[i + 1][i + 1] = 0;
            for (i64 x = i; x >= 0; x--){
                st[i + 1][x] = (st[i + 1][x + 1] + st[i][x]) % MOD;
            }
        }
    }

    // pt[n-1][n-1] = sum T(n-1, i) = valid permutations of size n respecting s
    cout << pt[n - 1][n - 1] << endl;
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
