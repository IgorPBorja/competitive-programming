//#define TESTCASES

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
#define i128 int128_t

template <typename ForwardIterator>
void print(ForwardIterator itr, int n, string sep=" ")
{
    for (int i = 0; i < n; i++)
    {
        cout << *itr << sep;
        ++itr;
    }
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> v){
    for (T x: v){
        cout << x << " ";
    }
    return os;
}

template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> v){
    cout << "(" << v.first << ", " << v.second << ")";
    return os;
}

i64 count(vector<vector<i64>>& grid){
    i64 n = grid.size();
    i64 m = grid[0].size();
    i64 cnt = 0;
    for (i64 i = 1; i + 1 < n; i++){
        for (i64 j = 1; j + 1 < m; j++){
            i64 l = grid[i][j - 1];
            i64 r = grid[i][j + 1];
            i64 u = grid[i - 1][j];
            i64 d = grid[i + 1][j];
            if (l == r && r == u && u == d && (d != grid[i][j])){
                ++cnt;
            }
        }
    }
    return cnt;
}

vector<pair<i64, i64>> diff(vector<vector<i64>>& g1, vector<vector<i64>>& g2){
    vector<pair<i64, i64>> diffvec;
    i64 n = g1.size();
    i64 m = g1[0].size();
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            if (g1[i][j] != g2[i][j]){
                diffvec.emplace_back(make_pair(i, j));
            }
        }
    }
    return diffvec;
}

void solve(){
    // amount of surrounded squares is monotonic
    i64 n, m, k;
    string _;
    cin >> n >> m >> k;
    cin.ignore();
    vector<vector<i64>> pics[k + 1];

    // read pics
    for (i64 p = 0; p < k + 1; p++){
        char c;
        pics[p] = vector<vector<i64>>(n, vector<i64>(m, 0));
        for (i64 i = 0; i < n; i++){
            for (i64 j = 0; j < m; j++){
                cin >> c;
                pics[p][i][j] = c - '0';
            }
            cin.ignore();
        }
    }


    vector<pair<i64, i64>> sorted_pics(k + 1); // (count, index)
    for (i64 i = 0; i < k + 1; i++){
        // the minus sign makes the sort reversed
        sorted_pics[i] = make_pair(-count(pics[i]), i);
    }
    sort(sorted_pics.begin(), sorted_pics.end());

    vector<string> ops;


    for (i64 i = 0; i + 1 < k + 1; i++){
        vector<pair<i64, i64>> diffvec = diff(pics[sorted_pics[i].second], pics[sorted_pics[i + 1].second]);
        if (diffvec.size() > 0){
            // there was diff
            for (auto[x, y]: diffvec){
                ops.emplace_back(to_string(1) + " " + to_string(x + 1) + " " + to_string(y + 1));
            }
        }
        ops.emplace_back(to_string(2) + " " + to_string(sorted_pics[i + 1].second + 1));
    }

    cout << sorted_pics[0].second + 1 << endl;
    cout << ops.size() << endl;
    for (string op: ops){
        cout << op << endl;
    }
}

int main(){
#ifdef TESTCASES
    int t;
    cin >> t;
    while (t--){
        solve();
    }
#else
    solve();
#endif
    fastio;
}
