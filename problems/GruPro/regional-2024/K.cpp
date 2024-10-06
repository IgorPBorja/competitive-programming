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
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl
#define printall(msg, container) cout << msg; for(auto it = begin(container); it != end(container); it++){cout << *it << "|";} cout << endl
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) }

#define all(x) begin(x), end(x)
 
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

const i64 MAXN = 100, MAXV = 100;
const i64 MAXSUM = MAXN * MAXV;
vector<bool> subset(MAXSUM + 1, false);
vector<i64> parent(MAXSUM + 1, -1);

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n);
    subset[0] = true;
    i64 s = 0;

    for (i64 i = 0; i < n; i++){
        cin >> a[i];
        s += a[i];
        auto copy = subset;
        for (i64 j = a[i]; j <= MAXN * MAXV; j++){
            if (subset[j - a[i]] && !subset[j]){
                parent[j] = i;  // ith should be on first set
            }
            copy[j] = subset[j] || subset[j - a[i]];
        }
        subset = copy;
    }
    // printmsg("parent=", parent.begin(), parent.begin() + 20);
    // printmsg("subset=", subset.begin(), subset.begin() + 20);

    if ((s % 2 == 1) || !subset[s / 2]){
        cout << -1 << endl;
    } else {
        vector<bool> is_first(n, false);
        i64 cur = s / 2;
        while (cur != 0){
            is_first[parent[cur]] = true;
            cur = cur - a[parent[cur]];
        }

        vector<i64> first, second;
        for (i64 i = 0; i < n; i++){
            if (is_first[i]){
                first.emplace_back(a[i]);
            } else {
                second.emplace_back(a[i]);
            }
        }
        // printall("first set=", first);

        vector<i64> order;
        i64 a = 0, b = 0, i = 0, j = 0;
        while (i < first.size() || j < second.size()){
            while (a < b || (a == b && i < first.size())){
                order.emplace_back(first[i]);
                a += first[i++];
            }
            while (b < a){
                order.emplace_back(second[j]);
                b += second[j++];
            }
        }
        for (i64 x: order){
            cout << x << " ";
        }
        cout << endl;
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
