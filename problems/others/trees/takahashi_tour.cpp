// The Republic of AtCoder has N cities numbered 1 through N and N−1 roads numbered 1 through N−1. Road i connects City Ai and City Bi bidirectionally. It is guaranteed that one can travel between every pair of cities using roads.

// Takahashi will depart City 1 and have a journey by repeating the following.

//     If there are unvisited cities that are directly connected to the city Takahashi is in now, he goes to the city with the smallest number among those cities.
//     Otherwise,
//         if he is in City 1, he ends the journey;
//         otherwise, he goes to the city he was in just before visiting the current city for the first time.

// Find the sequence of cities visited by Takahashi in the order he visits them.

// INPUT
// N
// A1 B1
// ⋮⋮
// A(N−1) B(N−1)
// OUTPUT 
// Print the sequence of cities visited by Takahashi in the order he visits them, including City 1 at the beginning and end of the journey, with spaces in between.

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

int n;
vi s, path;
vvi adj;
vb vis;
vi first_unvisited_neighbour;

int main(){
    fastio;
    cin >> n;
    adj.resize(n);
    int a, b;
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        a--; b--;
        adj[a].eb(b);
        adj[b].eb(a);
    }
    // sort adj in O(n log n)
    for (int i = 0; i < n; i++){
        sort(adj[i].begin(), adj[i].end());
    }
    vis.resize(n);
    vis.assign(n, false);
    first_unvisited_neighbour.resize(n);
    first_unvisited_neighbour.assign(n, 0);

    s.eb(0);
    while (!s.empty()){
        int u = s.back();
        vis[u] = true;
        bool flag = true;
        // slow approach: 
        // for (int v : adj[u]){
        //     if (!vis[v]){
        //         s.eb(v);
        //         path.eb(u);
        //         flag = false;
        //         break;
        //     }
        // }
        if (adj[u].size() > 0){
            while (first_unvisited_neighbour[u] < (int)adj[u].size() && vis[adj[u][first_unvisited_neighbour[u]]]){
                first_unvisited_neighbour[u]++;
            }
            if (first_unvisited_neighbour[u] < (int)adj[u].size()){
                s.eb(adj[u][first_unvisited_neighbour[u]]);
                path.eb(u);
                flag = false;
            }
        }
        if (flag){
            // pop
            path.eb(u);
            s.pop_back();
            if (u == 0){
                break; 
                // visited 0 for the second time
                // and had no other choices from 0
            }
        }
    }
    for (int u : path){
        cout << u + 1 << ' '; 
    }
}
