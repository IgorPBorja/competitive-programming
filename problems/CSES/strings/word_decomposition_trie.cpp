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
 
#define i32 int32_t
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

struct Trie {
    int idx = 1;
    const static int MAXN = (i64)1e6 + 10;
    int children[MAXN][26];
    int cnt[MAXN];  // cnt of words that end in that node

    Trie() {
        for (i64 i = 0; i < 26; i++){
            children[0][i] = -1;
        }
        cnt[0] = 0;
    }

    void add(const string& word, const int node = 0, int pos = 0){
        if (pos >= word.size()){
            ++cnt[node];
            return;
        } else {
            int i = word[pos] - 'a';
            if (children[node][i] == -1){
                children[node][i] = idx;
                cnt[idx] = 0;
                for (int j = 0; j < 26; j++){
                    children[idx][j] = -1;
                }
                ++idx;
            }
            add(word, children[node][i], pos+1);
        }
    }
};

void solve(){
    int k;
    string s;
    cin >> s >> k;
    const int n = s.size();
    Trie rev;
    for (int i = 0; i < k; i++){
        string t;
        cin >> t;
        reverse(t.begin(), t.end());
        rev.add(t);
        // for (int i = 0; i < rev.idx; i++){
        //     printmsg("children[" << i << "]=", rev.children[i], rev.children[i] + 26);
        // }
        // printmsg("cnt=", rev.cnt, rev.cnt + rev.idx);
    }


    i64 dp[n + 1];
    dp[0] = 1;
    for (int i = 0; i < n; i++){
        string t = "";
        int cur = 0; // current node
        dp[i + 1] = 0;
        for (int j = i; j >= 0; j--){
            // try substr s[j..i]^R which has size i - j + 1
            // all of this is O(1)
            t.push_back(s[j]);
            int new_node = rev.children[cur][s[j] - 'a'];
            if (new_node == -1){
                break;
            } else if (rev.cnt[new_node] > 0){
                dp[i + 1] = (dp[i + 1] + dp[j]) % MOD;
            }
            cur = new_node;
        }
    }
    cout << dp[n] << endl;
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
