#define TESTCASES
#define DEBUG
 
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

// i = amount of penalties done
i64 minstop(string& s, i64 i, i64 score1, i64 score2){
    // amount of even numbers in [i, m - 1]
    i64 pts1 = (s.size() + 1) / 2
    // amount of odd numbers in [i, m - 1]
    i64 pts2 = (s.size() - i) / 2 + (i % 2);
    
    if (i == s.size()){
        return s.size();
    } else if ((score1 + pts1 < score2) || (score2 + pts2 < score1)){
        return i;
    } else {
        if (s[i] == '1'){
            return minstop(s, i + 1, score1 + (i % 2), score2 + ((i + 1) % 2));
        } else if (s[i] == '0'){
            return minstop(s, i + 1, score1, score2);
        } else {
            return min(
                minstop(s, i + 1, score1 + (i % 2), score2 + ((i + 1) % 2)),
                minstop(s, i + 1, score1, score2)
            );
        }
    }
}

void solve(){
    string s;
    cin >> s;
    cout << minstop(s, 0, 0, 0) << endl;
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
