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

bool valid(string s){
    i64 cnt = 0;
    char last = 'x';
    for (char c: s){
        if (c == '-'){
            if (last == '-'){
                return false;  // can't have consecutive dashes
            }
            ++cnt;
        }
        last = c;
    }
    // cerr << "OK" << endl;
    if (s.size() - cnt != 10){
        // not 10 digits
        return false;
    }
    if (s[0] == '-' || s.back() == '-') return false;  // can't start or end with dash
    if (cnt > 3) return false;  // can't have more than 3 dashes
    if (cnt == 3 && s[s.size() - 2] != '-') return false;  // if 3 dashes, one separates the last digit

    i64 d = (s.back() == 'X') ? 10 : (s.back() - '0');
    i64 i = 10;
    i64 rem = 0;
    for (i64 j = 0; j < s.size() - 1; j++){
        char c = s[j];
        if (0 <= c - '0' && c - '0' < 10){
            rem += i * (c - '0');
            --i;
        }
    }
    if ((rem + d) % 11 != 0){
        return false;
    }
    return true;
}

// 3 inverted is 7

string transform(string s){
    string t = "978-" + s;
    i64 i = 1;
    i64 rem = 0;
    for (i64 j = 0; j < t.size() - 1; j++){
        char c = t[j];
        if (0 <= c - '0' && c - '0' < 10){
            rem += ( (i % 2 == 1) ? 1 : 3) * (c - '0');
            ++i;
        }
    }
    rem %= 10;
    if (i % 2 == 0){
        t.back() = ((7 * (10 - rem)) % 10) + '0';
    } else {
        t.back() = (10 - rem) + '0';
    }
    return t;
}

void solve(){
    string s;
    cin >> s;
    if (valid(s)){
        cout << transform(s) << endl;
    } else {
        cout << "invalid" << endl;
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
