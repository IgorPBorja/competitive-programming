#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vpi vector<pair<int, int>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define mp make_pair
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)

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
void print(ForwardIterator itr, int n, string sep = " ")
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

void calc_depth(vvi& tree, int s, vi& depth, vi& parent, int p = -1)
{
    depth[s] = 0;
    parent[s] = p;
    for (int t : tree[s])
    {
        if (t != parent[s])
        {
            calc_depth(tree, t, depth, parent, s);
            depth[s] = max(depth[s], depth[t] + 1);
        }
    }
}

int main()
{
    int n;
    cin >> n;

    vvi tree(n);
    int a, b;
    vi depth(n), parent(n); // can be undefined at first
    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        tree[a - 1].eb(b - 1);
        tree[b - 1].eb(a - 1);
    }
    calc_depth(tree, 0, depth, parent);

    // bfs now
    int diam = 0;
    vvi children_depth(n);
    for (int i = 0; i < n; i++)
    {
        for (int j : tree[i])
        {
            if (j != parent[i])
                children_depth[i].eb(depth[j]);
        }
        sort(children_depth[i].begin(), children_depth[i].end(), 
            [](int a, int b){return a > b;});
        if (children_depth[i].size() == 1)
        {
            diam = max(diam, depth[i]);
        } else if (children_depth[i].size() > 1) 
        {
            diam = max(diam, children_depth[i][0] + children_depth[i][1] + 2);
        }
    }
    cout << diam;
}