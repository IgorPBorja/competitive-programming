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
    string s, mask;
    cin >> s >> mask;

    vector<i64> pos[2], rev_pos[2];
    for (u64 i = 0; i < mask.size(); i++){
        pos[mask[i] - '0'].emplace_back(i);
        rev_pos[mask[i] - '0'].emplace_back(mask.size() - 1 - i);
    }
    // printmsg("pos[0]=", pos[0].begin(), pos[0].end());
    // printmsg("pos[1]=", pos[1].begin(), pos[1].end());
    // printmsg("rev_pos[0]=", rev_pos[0].begin(), rev_pos[0].end());
    // printmsg("rev_pos[1]=", rev_pos[1].begin(), rev_pos[1].end());

    i64 cnt = 0;  // as first (left) position of sofa
    for (u64 offset = 0; offset + mask.size() <= s.size(); offset++){
        bool ok = true, rev_ok = true;
        for (i64 c = 0; c < 2; c++){
            if (pos[c].size() != 0){
                char base_color = s[pos[c][0] + offset];
                for (i64 idx: pos[c]){
                    ok &= s[idx + offset] == base_color;
                }
            }

            if (rev_pos[c].size() != 0){
                char base_color = s[rev_pos[c][0] + offset];
                for (i64 idx: rev_pos[c]){
                    rev_ok &= s[idx + offset] == base_color;
                }
            }
        }
        if (ok || rev_ok) ++cnt;
    }
    cout << cnt << endl;
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
