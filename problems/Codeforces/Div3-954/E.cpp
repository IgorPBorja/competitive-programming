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

void solve(){
    i64 n, k;
    cin >> n >> k;

    i64 a[n];
    map<i64, vector<i64>> mods;
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        mods[a[i] % k].emplace_back(a[i] / k);
    }
    for (auto&[m, m_list]: mods){
        sort(m_list.begin(), m_list.end());
    }

    i64 odd_count = 0;
    i64 ans = 0;
    for (const auto&[_, m_list]: mods){
        const i64 s = m_list.size();
        i64 total_diff = 0;
        for (i64 i = 0; i + 1 < s; i += 2){
            total_diff += m_list[i + 1] - m_list[i];
        }
        if (s % 2 == 1){
            if (odd_count > 0 || (n % 2 == 0)){
                cout << -1 << endl;
                return;
            }
            ++odd_count;
        }
        if (s % 2 == 1 && s > 1){
            // must leave one out
            i64 leave_one_out[s];
            i64 standard[s];
            standard[1] = m_list[1] - m_list[0];
            leave_one_out[2] = min(m_list[2] - m_list[1], m_list[1] - m_list[0]);
            for (i64 i = 4; i < s; i += 2){
                // leave i out or leave j < i out
                standard[i - 1] = m_list[i - 1] - m_list[i - 2] + standard[i - 3];
                leave_one_out[i] = min(standard[i - 1], m_list[i] - m_list[i - 1] + leave_one_out[i - 2]);
            }
            total_diff = min(total_diff, leave_one_out[s - 1]);
        }
        ans += total_diff;
    }
    cout << ans << endl;
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
