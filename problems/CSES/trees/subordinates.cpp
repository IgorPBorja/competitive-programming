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

void subtree(vi children[], int dp[], int s)
{
    // dp[s] = 1;
    for (int t: children[s])
    {
        subtree(children, dp, t);
        dp[s] += dp[t] + 1; // t and its children
    }
}

int main()
{
    fastio;
    int n;
    cin >> n;
    int p[n];
    read(p + 1, n - 1);
    p[0] = -1;

    vi children[n];
    setval(children, n, vi(0));
    for (int i = 1; i < n; i++)
    {
        children[p[i] - 1].eb(i); // -1 fixes 1-index
    }
    int dp[n];
    setval(dp, n, 0);
    subtree(children, dp, 0);

    print(dp, n);
}