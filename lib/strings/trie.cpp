#include <bits/stdc++.h>
using namespace std;

template<int K>  // sum of characters in the set
struct Trie {
	int children[K][26];
	int cnt[K];  // cnt of each word
	int ptr = 1;

	Trie(){
		for (int i = 0; i < K; i++){
			for (int j = 0; j < 26; j++){
				children[i][j] = -1;
			}
			cnt[i] = 0;
		}
	}

	void insert(string& u, int i=0, int node=0){
		int idx = u[i] - 'a';
		if (children[node][idx] == -1){
			// create node
			children[node][idx] = ptr++;
		}
		if (i + 1 < u.size()){
			insert(u, i + 1, children[node][idx]);
		} else {
			++cnt[children[node][idx]];
		}
	}

	int search(string &u, int i=0, int node=0){
		if (i == u.size()){
			return cnt[node];
		} else {
			int idx = u[i] - 'a';
			if (children[node][idx] == -1){
				return 0;
			} else {
				return search(u, i + 1, children[node][idx]);
			}
		}
	}

	bool isleaf(int node){
		bool ok = true;
		for (int i = 0; i < 26; i++){
			ok = ok && children[node][i] == -1;
		}
		return ok;
	}

	void remove(string &u, int i=0, int node=0){
		int idx = u[i] - 'a';
		if (children[node][idx] != -1){
			remove(u, i + 1, children[node][idx]);
			if (isleaf(children[node][idx]) && cnt[children[node][idx]] == 0){
				children[node][idx] = -1;	
			}
		} else {
            // reached leaf
            cnt[node] = max(cnt[node] - 1, 0);
        }
	}
}; 
