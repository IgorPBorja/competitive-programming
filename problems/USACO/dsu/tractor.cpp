//LINK:
//https://usaco.org/index.php?page=viewproblem2&cpid=245

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

i64 n;
vector<vector<i64>> grid;

bool valid(i64 x, i64 y){
    return (0 <= x) && (x < n) && (0 <= y) && (y < n);
}

struct DSU{
    vector<vector<pair<i64, i64>>> p;
    vector<vector<i64>> size;
    i64 N;
    i64 max_size;

    DSU(i64 n){
        N = n;
        p.assign(n, vector<pair<i64, i64>>(n));
        size.assign(n, vector<i64>(n, 1));
        for (i64 i = 0; i < n; i++){
            for (i64 j = 0; j < n; j++){
                p[i][j] = {i, j};
            }
        }
        max_size = 1;
    }

    pair<i64, i64> find(pair<i64, i64> x){
        if (p[x.first][x.second] != x){
            p[x.first][x.second] = find(p[x.first][x.second]);
        }
        return p[x.first][x.second];
    }

    bool merge(pair<i64, i64> x, pair<i64, i64> y){
        pair<i64, i64> rx = find(x), ry = find(y);
        if (rx == ry) return false;

        if (size[rx.first][rx.second] > size[ry.first][ry.second]){
            swap(rx, ry);
        }
        p[rx.first][rx.second] = ry;
        size[ry.first][ry.second] += size[rx.first][rx.second];
        max_size = max(max_size, size[ry.first][ry.second]);
        return true;
    }
};

void solve(){
    cin >> n;

    grid.assign(n, vector<i64>(n));
    vector<tuple<i64, pair<i64, i64>, pair<i64, i64>>> edges;
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            cin >> grid[i][j];
        }
    }

    i64 dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < n; j++){
            for (i64 k = 0; k < 4; k++){
                if (valid(i + dx[k], j + dy[k]) && grid[i][j] >= grid[i + dx[k]][j + dy[k]]){
                    edges.emplace_back(tuple<i64, pair<i64, i64>, pair<i64, i64>>(
                        grid[i][j] - grid[i + dx[k]][j + dy[k]],
                        pair<i64, i64>(i, j),
                        pair<i64, i64>(i + dx[k], j + dy[k])
                    ));
                }
            }
        }
    }
    sort(edges.begin(), edges.end());
    DSU components(n);
    i64 curr_cost = 0;
    if (components.max_size >= (n * n + 1) / 2){
        cout << curr_cost << endl;
        return;
    }

    for (auto[d, p1, p2]: edges){
        curr_cost = max(curr_cost, d);
        components.merge(p1, p2);
        if (components.max_size >= (n * n + 1) / 2){
            cout << curr_cost << endl;
            return;
        }
    }
}
 
signed main(){
    fastio;
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
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
