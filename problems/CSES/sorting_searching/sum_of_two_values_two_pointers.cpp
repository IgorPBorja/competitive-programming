#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;
    int a[n], b[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b, b + n);
    int l = 0, r = n - 1;
    while (l < r)
    {
        if (b[l] + b[r] > x)
        {
            --r;
        } else if (b[l] + b[r] < x)
        {
            ++l;
        } else 
        {
            // found solution (l < r) in sorted array
            // now we need to find equivalent (l' < r') solution in the original
            // This can be done in O(n) with linear searching
            // 1. search for first ocurrence of b[l] --> i1
            // 2. search for last ocurrence of b[r] --> i2
            // guaranteed i1 != i2, even if b[l] == b[r] (because of the first/last ocurrence detail)
            // now l' = min(i1, i2) , r' = max(i1, i2)

            int i1, i2;
            for (int j = 0; j < n; j++)
            {
                if (a[j] == b[l])
                {
                    i1 = j;
                    break;
                }
            }
            for (int j = n - 1; j >= 0; j--)
            {
                if (a[j] == b[r])
                {
                    i2 = j;
                    break;
                }
            }
            // the +1 accounts for 1-indexing
            cout << min(i1, i2) + 1 << ' ' << max(i1, i2) + 1;
            return 0;
        }
    }
    cout << "IMPOSSIBLE";
}