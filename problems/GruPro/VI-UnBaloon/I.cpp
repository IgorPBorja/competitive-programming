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


struct TrieNode {
    i64 cnt = 0;
    TrieNode* children[26];

    TrieNode() : cnt(0) {
        for (i64 i = 0; i < 26; i++){
            children[i] = nullptr;
        }
    }
};

void add_word(string word, TrieNode* root){
    TrieNode* cur_node = root;
    for (char c: word){
        if (cur_node->children[c - 'a'] == nullptr){
            cur_node->children[c - 'a'] = new TrieNode();
        }
        cur_node = cur_node->children[c - 'a'];
    }
    ++cur_node->cnt;
}

string final_word = "";
bool has_ended = false;
i64 n, k;

// depth = size of current word
void dfs(TrieNode* node, string& word, i64 depth = 0){
    if (has_ended) return;
    if (depth >= k){
        // at existing word of size k
        return;
    }
    for (i64 c = 0; c < 26; c++){
        // cout << "at word=" << word << " children for c=" << c << " is " << node->children[c] << endl;
        word.push_back((char)(c + 'a'));
        if (!has_ended && (node->children[c] == nullptr || node->children[c]->cnt == 0)){
            // has no branch or branch is not full word
            has_ended = true;
            final_word = word;
            break;
        }
        if (node->children[c] != nullptr){
            dfs(node->children[c], word, depth + 1);
        }
        word.pop_back();
    }
}

void solve(){
    cin >> n >> k;
    TrieNode* trie = new TrieNode();
    for (i64 i = 0; i < n; i++){
        string s;
        cin >> s;
        add_word(s, trie);
    }

    string cur = "";
    dfs(trie, cur);
    cout << final_word << endl;
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
