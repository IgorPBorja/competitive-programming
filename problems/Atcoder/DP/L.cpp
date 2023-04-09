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

int main(){
    // dp[l][r][j] = score diff when (assuming equal scores at the start)
    // player j has to play in the subarray [l, r] (assuming optimal play)
    // 2n^2*size_type <= 2*3000^2*size_type <= 1.8e7*size_type bytes
    // since size_type == long long, it is probably 1.44e8 bytes = 144MB, OK
    //
    // each player can remove start or end
    // player 0 tries to maximize diff (which means he goes to the path that has largest diff)
    // player 1 tries to minimize diff
    // loop over possible subarray sizes (O(n^2) DP)
    fastio;
    int n;
    cin >> n;
    // long long ==> avoids overflow
    long long dp[n][n][2];
    long long a[n];
    read(a, n);

    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < n; j++){
    //         for (int k = 0; k < 2; k++){
    //             dp[i][j][k] = 0;
    //         }
    //     }
    // }

    for (int i = 0; i < n; i++)
    {
        // add to X (==> add to X-Y)
        dp[i][i][0] = a[i];
        // add to Y (==> subtract from X-Y)
        dp[i][i][1] = -a[i];
    }
    for (int s = 2; s <= n; s++){
        for (int i = 0; i + s - 1 < n; i++){
            // player 0 grabs a element x (a[i] or a[i + s - 1]) and add it to X
            // ==> add it to the diff X - Y
            dp[i][i + s - 1][0] = max(a[i] + dp[i + 1][i + s - 1][1],
                                      a[i + s - 1] + dp[i][i + s - 2][1]);
            // player 0 grabs a element x (a[i] or a[i + s - 1]) and add it to Y
            // ==> subtract it from the diff X - Y
            dp[i][i + s - 1][1] = min(-a[i] + dp[i + 1][i + s - 1][0],
                                      -a[i + s - 1] + dp[i][i + s - 2][0]);
        }
    }
    cout << dp[0][n - 1][0];
}
