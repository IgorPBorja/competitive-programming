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

void solve(const string s){
	const i64 n = s.size();	

	set<string> subseq; // NOTE: question guarantees |subseq| <= 1000
	subseq.insert("");
	for (i64 pivot = 0; pivot < n; pivot++){
		vector<string> delta;
		for (string t: subseq){
			t += s[pivot];
			delta.emplace_back(t);
		}
		for (string t: delta){
			subseq.insert(t);
		}
	}
	subseq.erase("");
	for (string t: subseq){
		cout << t << endl;
	}
	cout << endl;
}
 
signed main(){
	fastio;
	string s;
	while (getline(cin, s)){
		// cerr << "s='" << s << "'" << endl;
		solve(s);
	}
}
