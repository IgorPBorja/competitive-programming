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

// since k <= 10^9, 
// log(k) <= 30
// since n <= 2*10^5
int f_lifted[30][200000];
int n, q;

int main(){
    fastio;
    cin >> n >> q;
    for (int i = 0; i < n; i++){
        int j;
        cin >> j;
        j--;
        f_lifted[0][i] = j;
    }
    // O(n log k)
    for (int i = 1; i < 30; i++){
        for (int j = 0; j < n; j++){
            f_lifted[i][j] = f_lifted[i-1][f_lifted[i-1][j]];
        }
    }

    int x, k;
    // O (q log k)
    for (int i = 0; i < q; i++){
        cin >> x >> k;
        --x; // correct to 0-indexing
        // O(log k)
        int curr = x;
        for (int j = 0; j < 30; j++){
            bool b_j = k & (1 << j);
            if (b_j){
                curr = f_lifted[j][curr];
                // apply f^{2^j} to curr
            }
        }
        cout << curr + 1 << endl;
    }
    // Total complexity: O((n + q) log k)
}