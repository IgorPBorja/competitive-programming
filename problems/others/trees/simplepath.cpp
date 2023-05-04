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

template <typename ForwardIterator>
void read(ForwardIterator itr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> *itr;
        ++itr;
    } 
}
template <typename ForwardIterator>
void print(ForwardIterator itr, int n, string sep=" ")
{
    for (int i = 0; i < n; i++)
    {
        cout << *itr << sep;
        ++itr;
    }
}
template <typename ForwardIterator, typename T>
void setval(ForwardIterator itr, int n, T v)
{
    for (int i = 0; i < n; i++) 
    {
        *itr = v;
        ++itr;
    }
}

template <typename ForwardIterator>
void read_pairs(ForwardIterator itr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> itr->first >> itr->second;
        ++itr;
    }
}

int n, x, y;
vi parent_x;
vb visited;
vvi adj;

void dfs(int s){
    for (int u : adj[s]){
        if (u == parent_x[s]) continue;
        if (visited[u]) continue;
        parent_x[u] = s;
        visited[u] = true;
        dfs(u);
    }
}
 
int main(){
    fastio;
    cin >> n >> x >> y;
    --x; --y;
    parent_x.resize(n);
    adj.resize(n);
    for (int i = 0; i < n - 1; i++){
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].eb(v);
        adj[v].eb(u);
    }
    visited.resize(n);
    visited.assign(n, false);
    visited[x] = true;
    parent_x[x] = -1;
    dfs(x);

    // building path from x to y
    vi path;
    int curr = y;
    while (curr != -1){
        path.eb(curr + 1); // +1 corrects from 0-indexing to 1-indexing
        curr = parent_x[curr];
    }
    reverse(path.begin(), path.end());
    print(path.begin(), path.size());
    cout << endl;
}
