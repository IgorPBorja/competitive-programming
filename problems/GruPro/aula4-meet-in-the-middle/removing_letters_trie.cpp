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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

struct TrieNode {
	char c;
	TrieNode* leaf[26];

	TrieNode(char c){
		this->c = c;
		memset(leaf, NULL, 26 * sizeof(TrieNode*));
	}
	TrieNode* add(char c){
		TrieNode* node = new TrieNode(c); // create on the heap so it persists
		this->leaf[c - 'a'] = node;
		return node;
	}
};

void dfs(TrieNode* node, string& cur){
	if (node->c != '+'){ // placeholder for root
		cur += node->c;
		cout << cur << endl;
	}
	for (i64 i = 0; i < 26; i++){
		if (node->leaf[i] != NULL){
			dfs(node->leaf[i], cur);
		}
	}
	if (cur.size() > 0){
		cur.pop_back();
	}
}


void solve(const string s){
	vector<TrieNode*> lazy[26];
	TrieNode* root = new TrieNode('+');
		
	for (i64 i = 0; i < 26; i++){
		lazy[i].emplace_back(root);
	}

	const i64 n = s.size();
	for (i64 i = 0; i < n; i++){
		// create new sequences from s[i]
		vector<TrieNode*> created;
		for (TrieNode* node: lazy[s[i] - 'a']){
			TrieNode* new_node = node->add(s[i]);
			created.emplace_back(new_node);
		}
		lazy[s[i] - 'a'].clear();
		for (i64 j = 0; j < 26; j++){
			for (TrieNode* new_node: created){
				lazy[j].emplace_back(new_node);
			}
		}
	}
	string cur_subseq = "";
	dfs(root, cur_subseq); 
	cout << endl;
}
 
signed main(){
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
	fastio;
	string s;
	while (getline(cin, s)){
		s.erase(remove(s.begin(), s.end(), ' '), s.end());
		solve(s);
	}
}
