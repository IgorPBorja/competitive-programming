#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>

int main()
{
    int n, k;
    cin >> n >> k;
    int a[n];
    for (int i  = 0; i < n; i++) cin >> a[i];

    map<int, int> pos; // stores pos (range 0 to d - 1)
    int d = 0;
    for (int i = 0; i < n; i++) pos[a[i]] = -1;
    for (int i = 0; i < n; i++)
    {
        if (pos[a[i]] == -1)
        {
            pos[a[i]] = d;
            ++d;
        } 
    }

    int cnt[d], r = 0, curr_d = 1;
    long long total = 0;
    for (int i = 0; i < d; i++) cnt[i] = 0;
    ++cnt[pos[a[0]]];

    for (int l = 0; l < n; l++)
    {
        // remove previous left
        if (l > 0)
        {
            --cnt[pos[a[l-1]]];
            if (cnt[pos[a[l - 1]]] == 0) --curr_d;
        }
        while (r + 1 < n 
                && 
                curr_d + ((cnt[pos[a[r + 1]]] == 0) ? 1 : 0) <= k)
        {
            curr_d += ((cnt[pos[a[r + 1]]] == 0) ? 1 : 0);
            ++cnt[pos[a[r + 1]]];
            ++r;
        }
        // now r is the last possible position
        // we can use any right position from [l,r] (inclusive)
        total += (long long)(r - l + 1);
    }
    cout << total << '\n';
}