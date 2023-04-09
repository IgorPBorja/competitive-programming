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

const int int_INF = 1e9;
const long long ll_INF = 2e18;

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

int main(){
    fastio;
    int n;
    cin >> n;
    long long a[n + 1];
    a[0] = 0;
    read(a + 1, n);
    for (int i = 1; i < n + 1; i++){
        a[i] += a[i-1];
    }

    // dp[i][j] = cost of solving [i,...,j-1] for j > i
    long long dp[n + 1][n + 1];
    for (int i = 0; i < n + 1; i++){
        for (int j = 0; j < n + 1; j++)
            dp[i][j] = 0;
    }
    // dp[i][j] = min(dp[i][k] + dp[k][j] + a[i] + ... + a[j - 1])
    // for i < k < j
    // since both [i,...,k-1] and [k,...,j-1] have to be non-empty
    // e.g: if j - i == 2 (size 2 subarray
    // dp[i][i + 2] = min(INF, dp[i][i + 1] + dp[i + 1][i + 2] + a[i] + a[i + 1])

    for (int s = 2; s <= n; s++){
        for (int i = 0; i + s <= n; i++){
            dp[i][i + s] = ll_INF;
            for (int j = i + 1; j < i + s; j++){
                dp[i][i + s] = min(dp[i][i + s],
                                   dp[i][j] + dp[j][i + s] + a[i + s] - a[i]);
            }
        }
    }
    // for (int i = 0; i < n + 1; i++){
    //     for (int j = 0; j < n + 1; j++){
    //         cout << setw(10) << dp[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    cout << dp[0][n];
}
