// USE BFS to calculate minimum distance
// (an unweighted version of a dijkstra)
// and store at each vertice its previous node (in the optimal path)

#include <bits/stdc++.h>
using namespace std;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1}; 

bool valid(int x, int y, int n, int m)
{
    return (0 <= x && x < n && 0 <= y && y < m);
}

void bfs(vector<vector<int>>& grid,
        vector<vector<pair<int,int>>>& prev,
        vector<vector<int>>& dist,
        vector<vector<bool>>& vis,
        pair<int,int> p)
{   
    int n = grid.size(), m = grid[0].size();
    queue<pair<int, int>> q;
    q.emplace(p);
    dist[p.first][p.second] = 0;
    prev[p.first][p.second] = make_pair(-1, -1);
    vis[p.first][p.second] = true;
    while (!q.empty())
    {
        pair<int, int> p2 = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            if (valid(p2.first + dx[i], p2.second + dy[i], n, m)
                && grid[p2.first + dx[i]][p2.second + dy[i]] == 0)
            {
                if (dist[p2.first + dx[i]][p2.second + dy[i]] + 1 <
                    dist[p2.first][p2.second])
                {
                    dist[p2.first][p2.second] = dist[p2.first + dx[i]][p2.second + dy[i]] + 1;
                    prev[p2.first][p2.second] = make_pair(p2.first + dx[i], p2.second + dy[i]);
                }
                if (!vis[p2.first + dx[i]][p2.second + dy[i]])
                {
                    vis[p2.first + dx[i]][p2.second + dy[i]] = true; // marking visited here
                    // prevents adding vertex to queue twice
                    // loop invariant: only visited vertices on queue
                    q.emplace(p2.first + dx[i], p2.second + dy[i]);
                }
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> grid(n, vector<int>(m)), dist(n, vector<int>(m, 2e9));
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    vector<vector<pair<int, int>>> prev(n, vector<pair<int,int>>(m, make_pair(-1, -1)));
    
    char c;
    pair<int, int> p, q;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> c;
            if (c == '#')
            {
                grid[i][j] = 1;
            } else 
            {
                grid[i][j] = 0;
            }
            if (c == 'A')
            {
                p.first = i; p.second = j;
            }
            if (c == 'B')
            {
                q.first = i; q.second = j;
            }
        }
    }
    bfs(grid, prev, dist, vis, p);

    if (dist[q.first][q.second] == 2e9)
    {
        cout << "NO";
        return 0;
    } else
    {
        cout << "YES\n";

        vector<pair<int,int>> reverse_path;
        pair<int, int> curr = q;
        while (curr.first != -1)
        {
            reverse_path.emplace_back(curr);
            curr = prev[curr.first][curr.second];
        }
        cout << reverse_path.size() - 1 << '\n';
        // for (int i = 0; i < reverse_path.size(); i++)
        // {
        //     cout << reverse_path[i].first << ' ' << reverse_path[i].second << '\n';
        // }
        
        string moves_reverse = "";
        for (int i = 0; i < reverse_path.size() - 1; i++)
        {
            int delta_x = reverse_path[i].first - reverse_path[i + 1].first;
            int delta_y = reverse_path[i].second - reverse_path[i + 1].second;
            if (delta_x == 1)
            {
                moves_reverse += "D";
            } else if (delta_x == -1)
            {
                moves_reverse += "U";
            } else if (delta_y == 1)
            {
                moves_reverse += "R";
            } else if (delta_y == -1)
            {
                moves_reverse += "L";
            }
        }

        for (int i = (int)moves_reverse.size() - 1; i >= 0; i--)
        {
            cout << moves_reverse[i];
        }
    }
}