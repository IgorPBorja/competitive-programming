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

template<int K, int B>
struct BitTrie {
    int c[2][B * K + 1];
    int cnt[B * K + 1];
    int ptr = 1;

    BitTrie(){
        for (int i = 0; i <= B * K; i++){
            c[0][i] = c[1][i] = -1;
            cnt[i] = 0;
        }
    }

    void insert(const int n, int pos = 1, int node = 0){
        if (pos > B){
            ++cnt[node];
        } else {
            int bit = (n & (1ll << (B - pos))) >> (B - pos);
            if (c[bit][node] == -1){
                // create node
                c[bit][node] = ptr++;
            }
            insert(n, pos + 1, c[bit][node]);
        }
    }

    // search for best possible correspondence to mask
    int _search(const int n, int pos = 1, int node = 0){
        if (pos > B){
            return 0;
        } else {
            int bit = (n & (1ll << (B - pos))) >> (B - pos);
            if (c[bit][node] == -1){
                // could not match
                // if c[bit][node] is null, then c[1 - bit][node] is not null otherwise
                // would not have entered node (unless trie is empty)
                return ((1ll - bit) << (B - pos)) + _search(n, pos + 1, c[1 - bit][node]);
            } else {
                return ((1ll * bit) << (B - pos)) + _search(n, pos + 1, c[bit][node]);
            }
        }
    }

    int search(const int n){
        if (c[0][0] == c[1][0] && c[1][0] == -1){
            return 0;  // empty trie
        }
        return _search(n);
    }

    void remove(const int n, int pos = 1, int node = 0){
        if (pos > B){
            cnt[node] = max(cnt[node] - 1, 0);
        } else {
            // read next bit
            int bit = (n & (1ll << (B - pos))) >> (B - pos); 
            int next = c[bit][node];
            remove(n, pos + 1, next);
            if (c[0][next] == c[1][next] && c[1][next] == -1 && cnt[next] == 0){
                c[bit][node] = -1; // delete
            }
        }
    }
};

void solve(){
    const int K = (int)2e5 + 1, B = 30;

    int q, x;
    string mode;
    BitTrie<K, B> T;
    cin >> q;
    T.insert(0);
    for (int i = 0; i < q; i++){
        cin >> mode >> x;
        if (mode == "+"){
            T.insert(x);
        } else if (mode == "-"){
            T.remove(x);
        } else if (mode == "?"){
            int not_x =  (1ll << B) - 1 - x;
            int y = T.search(not_x);
            // cout << "found y=" << y << endl;
            cout << (x ^ y) << endl;
        }
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
