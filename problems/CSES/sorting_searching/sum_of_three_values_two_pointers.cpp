//NOT WORKING

#include <bits/stdc++.h>
using namespace std;

template <typename T> 
void find3indexes(T a[], int n, T x, T y, T z, int ans[3])
{
    // we have x <= y <= z
    // find index(x) as first ocurrence of x
    // find index(y) as:
    /*
        first ocurrence of y if y != x
        second ocurrence of x if y == x
    */
   // find index(z) as last ocurrence of z
   for (int i = 0; i < n; i++)
   {
        if (a[i] == x)
        {
            ans[0] = i;
            break;
        }
   }
   if (y != x)
   {
        for (int i = 0; i < n; i++)
        {
            if (a[i] == y)
            {
                ans[1] = i;
                break;
            }
        }
   } else 
   {
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] == y)
            {
                if (cnt == 0)
                {
                    ++cnt;
                }
                else{
                    ans[1] = i;
                    break;
                }
            }
        }
   }
   for (int i = n - 1; i >= 0; i--)
   {
        if (a[i] == z)
        {
            ans[2] = i;
            break;
        } 
   }
}

int main()
{
    // O(nlogn + n^2) = O(n^2) solution
    int n, ans[3];
    long long x; // avoid overflow
    cin >> n >> x;
    long long a[n], b[n]; // avoid overflow with 1e9 + 1e9 + 1e9
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(a, a + n);
    int r = 0;
    for (int l = 0; l < n; l++)
    {
        // once for the change in l
        for (int mid = l + 1; mid < r; mid++)
        {
            if (a[l] + a[r] + a[mid] == x)
            {
                find3indexes(b, n, a[l], a[mid], a[r], ans);
                sort(ans, ans + 3);
                for (int j = 0; j < 3; j++)
                    cout << ans[j] + 1 << ' ';
                return 0;
            }
        }
        while (r + 1 < n && a[l] + a[r + 1] <= x) // can move
        {
            // since a[] is a non-negative array 
            // there is no way a solution would have a[l] + a[r] > x
            // (since a[mid] >= 0)
            ++r;
            // once for the change in r
            for (int mid = l + 1; mid < r; mid++)
            {
                if (a[l] + a[r] + a[mid] == x)
                {
                    find3indexes(b, n, a[l], a[mid], a[r], ans);
                    sort(ans, ans + 3);
                    for (int j = 0; j < 3; j++)
                        cout << ans[j] + 1 << ' ';
                    return 0;
                }
            }
        }
    }
    cout << "IMPOSSIBLE";
}