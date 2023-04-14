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
#define MOD (int)(1e9 + 7)
#define INF (int)(2e9)

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

int f(int dp[], vvi& a, int b){
    int n = (int)a.size();

    if (dp[b] != -INF){
        return dp[b];
    } else {
        dp[b] = 0;

        int zeroes = 0;
        for (int i = 0; i < n; i++){
            zeroes += ((b >> i) % 2 == 0) ? 1 : 0;
        }
        for (int i = 0; i < n; i++){
            if ((b >> i) % 2 == 0 && a[n - zeroes][i] == 1){
                dp[b] = (dp[b] + f(dp, a, b + (1 << i))) % MOD;
            }
        }
        return dp[b];
    }
}

int main(){
    fastio;
    /** Let dp[b(1)]...[b(n)]
     * be how many matchings of
     * b^{-1}(0) = k people
     * there are using only positions j such that b_j != 0
     * I.E matching
     * pos n-k with the first pos zero
     * ...
     * pos n-1 with the last pos zero
     * Then dp[1]...[1] = 1 (the empty match)
     *
     * AND (setting k = )
     * dp[b(1)]...[b(n)] =
     * sum_{b(i) = 0 && a[k][i]==1}dp[b(1)]...[1-b(i)]...[b(n)]
     *
     * since each summand represents pairing pos k with
     * pos b(i)
     * */
    int n;
    cin >> n;
    vvi a(n, vi(n));
    for (int i = 0; i < n; i++){
        read(a[i].begin(), n);
    }

    int dp[1 << n];
    setval(dp, 1 << n, -INF);
    dp[(1 << n) - 1] = 1; // empty match

    f(dp, a, 0);
    cout << dp[0];
}
