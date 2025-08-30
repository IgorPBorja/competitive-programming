// #define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

/*
a sequence is valid iff open[i] >= closed[i] at any given step. Initial sequence is valid

When picking a pair (i, j) with i < j, open at i, closed at j
we decrement open over i+1..n and decrement closed over j+1..n

so danger lies in i+1..j-1: if at any time open[k] = closed[k] there, it is an invalid pair
Putting a[i] = 1 iff open[i] == closed[i] else a[i] = 0, we can only pick pairs inside the 0 blocks
*/

void solve(){
    i64 n;
    string s;

    i64 compatible = 0;
    cin >> n >> s;
    vector<i64> open(n, 0), closed(n, 0), pos_1;
    pos_1.emplace_back(-1);
    for (i64 i = 0; i < n; i++){
        if (i > 0){
            open[i] = open[i - 1];
            closed[i] = closed[i - 1];
        }
        if (s[i] == '(') ++open[i];
        else ++closed[i];
        if (open[i] == closed[i]) pos_1.emplace_back(i);
    }
    pos_1.emplace_back(n);
    i64 num_blocks = pos_1.size();
    for (i64 i = 0; i + 1 < num_blocks; i++){
        i64 bopen = 0, bclosed = 0;
        for (i64 j = max(pos_1[i], (i64)0); j <= min(pos_1[i + 1], n - 1); j++){
            bopen += (s[j] == '(');
            bclosed += (s[j] == ')');
        }
        for (i64 j = max(pos_1[i], (i64)0); j <= min(pos_1[i + 1], n - 1); j++){
            if (s[j] == '('){
                compatible += bclosed;
            } else {
                --bclosed;
            }
        }
    }

    i64 total_pairs = 0;
    i64 total_closed = closed.back();
    for (i64 i = 0; i < n; i++){
        if (s[i] == '('){
            total_pairs += total_closed;
        } else {
            --total_closed;
        }
    }
    // cout << "total=" << total_pairs << " compatible=" << compatible << endl;
    cout << total_pairs - compatible << endl;
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
