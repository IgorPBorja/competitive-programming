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
    // dp[i][j] = winner if player j (0 <= j <= 1) is playing and there are i (0 <= i <= k) stones

    fastio;
    int n, k;
    cin >> n >> k;
    int a[n];
    read(a, n);
    // sort(a, a + n); // not needed, already in order
    int dp[k + 1][2];
    for (int i = 0; i < a[0]; i++){
        // loses immediately
        dp[i][0] = 1;
        dp[i][1] = 0;
    }
    dp[a[0]][0] = 0;
    dp[a[0]][1] = 1;

    for (int i = a[0] + 1; i <= k; i++){
        // dp[i][j] = j if there is a <= i in A such that dp[i-a][1-j] = j, else 1-j
        // <= 2*N*K <= 2e7 operations, so it works
        for (int j = 0; j <= 1; j++){
            bool can_win = false;
            for (int l = 0; l < n && a[l] <= i; l++){
                if (dp[i - a[l]][1 - j] == j){
                    can_win = true;
                }
            }
            if (can_win){
                dp[i][j] = j;
            } else {
                dp[i][j] = 1 - j;
            }
        }
    }
    if (dp[k][0] == 0){
        cout << "First";
    } else {
        cout << "Second";
    }
}
