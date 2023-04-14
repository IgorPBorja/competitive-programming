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
    fastio;
    int n;
    long long x;
    cin >> n >> x;
    pair<long long, long long> a[n];
    for (int i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i; // pos
    }
    sort(a, a + n);

    for (int i = 0; i < n; i++){
        for (int j = i + 1; j < n; j++){
            // bsearch in [j + 1, ... n)
            int lo = j + 1, hi = n - 1;
            int k = -1;
            while (lo <= hi){
                int mid = lo + (hi - lo) / 2;
                if (a[i].first + a[j].first + a[mid].first == x){
                    cout << a[i].second + 1 << ' ' << a[j].second + 1 << ' ' << a[mid].second + 1;
                    return 0;
                } else if (a[i].first + a[j].first + a[mid].first > x){
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
        }
    }
    cout << "IMPOSSIBLE";
}
