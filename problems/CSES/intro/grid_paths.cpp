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

#define colblock(i) (vis[0][i] && vis[1][i] && vis[2][i] && vis[3][i] && vis[4][i] && vis[5][i] && vis[6][i])
#define rowblock(i) (vis[i][0] && vis[i][1] && vis[i][2] && vis[i][3] && vis[i][4] && vis[i][5] && vis[i][6])
#define deadend(px, py) (\
    (px == 0 || vis[px - 1][py]) && (px == N - 1 || vis[px + 1][py]) \
    && (py == 0 || vis[px][py - 1]) && (py == N - 1 || vis[px][py + 1]) \
)


const i64 N = 7;
const i64 M = 48;

map<char, pair<i64, i64>> dir_map{{
    {'L', {0, -1}},
    {'R', {0, 1}},
    {'U', {-1, 0}},
    {'D', {1, 0}}
}};
const vector<char> dir = {'L', 'R', 'U', 'D'};
bool vis[N][N];
string s;
i64 call_cnt = 0;

i64 backtrack(i64 i, i64 px, i64 py){
    ++call_cnt;
    if (px < 0 || px >= N || py < 0 || py >= N){
        return 0;
    }
    // optimization 1:  early finish
    if (i < M && px == N - 1 && py == 0){
        return 0;
    }
    else if (i == M && (px != N - 1 || py != 0)){
        return 0;
    } else if (i == M && px == N - 1 && py == 0){
        return 1;
    }
    // optimization 2: can't go left or can't go down
    if ((py > 0 && colblock(py - 1)) || (px < N - 1 && rowblock(px + 1))){
        return 0;
    }
    // optimization 3: dead ends
    if (deadend(px, py)){
        return 0;
    }
    // cerr << "i=" << i << " px=" << px << " py=" << py << endl;
    i64 cnt = 0;
    vis[px][py] = true;
    if (s[i] == '?'){
        for (char c: dir){
            i64 px2 = px + dir_map[c].first;
            i64 py2 = py + dir_map[c].second;
            if (px == px2 && py == py2) cerr << "i=" << i << " px=" << px << " py=" << py << endl;
            cnt += backtrack(i + 1, px2, py2);
        }
    } else if (s[i] == 'L' || s[i] == 'R' || s[i] == 'U' || s[i] == 'D'){
        i64 px2 = px + dir_map[s[i]].first;
        i64 py2 = py + dir_map[s[i]].second;
        if (px == px2 && py == py2) cerr << "i=" << i << " px=" << px << " py=" << py << endl;
        cnt += backtrack(i + 1, px2, py2);
    }

    vis[px][py] = false;
    return cnt;
}



void solve(){
    bool vis[N][N];
    for (i64 i = 0; i < N; i++) for (i64 j = 0; j < N; j++) {vis[i][j] = false;}
    vis[0][0] = true;
    cin >> s;
    i64 ans = backtrack(0, 0, 0);
    cout << ans << endl;
    cout << call_cnt << endl;
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
