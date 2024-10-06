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

const i64 INF = 2e18;

vector<vector<i64>> simultaneous_bfs(vector<vector<i64>> &grid, vector<pair<i64, i64>> &monsters){
    // we work "radially" from each monster
    // each monsters takes a step (put all unvisited neighbors on queue)
    // the first time it visits a square will be with the min distance since bfs visits vertices
    // in distance order
    const i64 n = grid.size(), m = grid[0].size();
    vector<vector<i64>> dist(n, vector<i64>(m, INF));
    queue<pair<pair<i64, i64>, i64>> q;
    for (pair<i64, i64> p: monsters){
        q.emplace(make_pair(p, (i64)0));
    }

    auto valid = [n, m](i64 i, i64 j){
        return 0 <= i && i < n && 0 <= j && j < m;
    };

    while (!q.empty()){
        auto[p, d] = q.front();
        q.pop();
        if (dist[p.first][p.second] < INF){
            continue;
        }

        dist[p.first][p.second] = d;

        i64 dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
        for (i64 i = 0; i < 4; i++){
            i64 x2 = p.first + dx[i], y2 = p.second + dy[i];
            if (valid(x2, y2) && dist[x2][y2] == INF && grid[x2][y2] > 0){
                q.emplace(make_pair(make_pair(x2, y2), d + 1));
            }
        }
    }
    return dist;
}

struct QueueNode {
    pair<i64, i64> pos;
    pair<i64, i64> parent;
    i64 dist;

    QueueNode(pair<i64, i64> pos, pair<i64, i64> parent, i64 dist) : pos(pos), parent(parent), dist(dist) {};
    QueueNode(pair<i64, i64> pos) : pos(pos), parent(make_pair(-1, -1)), dist(0) {};
};

char get_move(pair<i64, i64> parent, pair<i64, i64> pos){
    i64 dx = pos.first - parent.first;
    i64 dy = pos.second - parent.second;
    if (dx == -1){
        return 'U';
    } else if (dx == 1){
        return 'D';
    } else if (dy == -1){
        return 'L';
    } else {
        return 'R';
    }
}

vector<char> replay_steps(vector<vector<pair<i64, i64>>> &prev, pair<i64, i64> p0){
    vector<char> steps;
    pair<i64, i64> cur = p0;
    while (prev[cur.first][cur.second] != make_pair((i64)(-1),(i64)(-1))){
        steps.emplace_back(get_move(prev[cur.first][cur.second], cur));
        cur = prev[cur.first][cur.second];
    }
    reverse(steps.begin(), steps.end());
    return steps;
}

vector<char> finalbfs(vector<vector<i64>> &grid, vector<vector<i64>> &monster_dist, pair<i64, i64> a){
    const i64 n = grid.size(), m = grid[0].size();
    queue<QueueNode> q;
    q.emplace(QueueNode(a));
    vector<vector<i64>> dist(n, vector<i64>(m, INF));
    vector<vector<pair<i64, i64>>> prev(n, vector<pair<i64, i64>>(m, make_pair(-1,-1)));

    auto valid = [n, m](i64 i, i64 j){
        return 0 <= i && i < n && 0 <= j && j < m;
    };

    while (!q.empty()){
        QueueNode node = q.front();
        q.pop();
        if (dist[node.pos.first][node.pos.second] < INF){
            continue;
        }
        dist[node.pos.first][node.pos.second] = node.dist;
        prev[node.pos.first][node.pos.second] = node.parent;

        i64 dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
        for (i64 i = 0; i < 4; i++){
            i64 x2 = node.pos.first + dx[i], y2 = node.pos.second + dy[i];
            if (valid(x2, y2) && dist[x2][y2] == INF && grid[x2][y2] > 0 && monster_dist[x2][y2] > node.dist + 1){
                q.emplace(QueueNode(make_pair(x2, y2), node.pos, node.dist + 1));
            }
        }
    }

    for (i64 i = 0; i < n; i++){
        if (dist[i][0] < INF){
            return replay_steps(prev, make_pair(i, 0));
        } else if (dist[i][m - 1] < INF){
            return replay_steps(prev, make_pair(i, m - 1));
        }
    }
    for (i64 i = 0; i < m; i++){
        if (dist[0][i] < INF){
            return replay_steps(prev, make_pair(0, i));
        } else if (dist[n - 1][i] < INF){
            return replay_steps(prev, make_pair(n - 1, i));
        }
    }
    return {};
}

void solve(){
    i64 n, m;
    cin >> n >> m;

    vector<vector<i64>> grid(n, vector<i64>(m));
    pair<i64, i64> a;
    vector<pair<i64, i64>> monsters;
    string row;

    for (i64 i = 0; i < n; i++){
        cin >> row;
        for (i64 j = 0; j < m; j++){
            if (row[j] == 'A') a = make_pair(i, j);
            if (row[j] == 'M'){
                monsters.emplace_back(make_pair(i, j));
            }
            if (row[j] == '#') {
                grid[i][j] = 0;
            } else {
                grid[i][j] = 1;
            }
        }
    }

    vector<vector<i64>> monster_dist = simultaneous_bfs(grid, monsters);
    vector<char> steps = finalbfs(grid, monster_dist, a);
    if (steps.size() > 0 || a.first == 0 || a.first == n - 1 || a.second == 0 || a.second == m - 1){
        cout << "YES" << endl;
        cout << steps.size() << endl;
        for (char c: steps){
            cout << c;
        }
        cout << endl;
    } else {
        cout << "NO" << endl;
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
