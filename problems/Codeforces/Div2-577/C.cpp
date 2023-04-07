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

#define int long long

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

/**
 *Strategy: sort the array
 *Then, to increase the median element, we need to increase everything that comes after
 *to the same value or higher
 *Let a[i] be the median
 *First, we check if we can put a[i] = ... = a[j] for each j > i (raise to a[j])
 *In O(n), using prefix sums
 *If we can, _then_ we can start binary search
 *
 **/

signed main(){
    fastio;
    int n;
    int k;
    cin >> n >> k;
    int a[n];
    read(a, n);
    sort(a, a + n);

    int b[n + 1];
    b[0] = 0;
    for (int i = 1; i < n + 1; i++){
        b[i] = a[i - 1] + b[i - 1];
    }
    int m = n / 2;
    int max_median = a[m];

    int l = a[m], r = a[n - 1] + k/(n - m);
    while (l <= r){
        int mid = l + (r - l)/2;
        // bsearch last a[i] <= mid
        int l2 = m, r2 = n - 1, pos = m;
        while (l2 <= r2){
            int mid2 = l2 + (r2 - l2)/2;
            if (a[mid2] <= mid){
                pos = mid2;
                l2 = mid2 + 1;
            } else {
                r2 = mid2 - 1;
            }
        }
        // now the delta is (pos - m + 1)*mid - (a[m] + ... + a[pos])
        int delta = (pos - m + 1)*mid - (b[pos + 1] - b[m]);
        if (delta <= k){
            max_median = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    // Complexity: O(log(max a[i] + k) * log (n))

    cout << max_median;
}
