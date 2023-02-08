#include <bits/stdc++.h>
using namespace std;

/* k =3
10 5 1 12 9 5 14

1 5 5 9 10 12 14
*/

int main()
{
    freopen("diamond.in","r",stdin);
    freopen("diamond.out","w", stdout);

    int n, k;
    cin >> n >> k;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n);

    int r[n]; // r[i] = ending pos of max subarray starting at i
    for (int i = 0; i < n; i++)
    {
        r[i] = i;
    }


    int r1 = 0;
    for (int l1 = 0; l1 < n; l1++)
    {
        while (r1 + 1 < n && a[r1 + 1] - a[l1] <= k)
        {
            ++r1;    
        }
        r[l1] = r1;
    }

    int suffix[n + 1];
    suffix[n] = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        suffix[i] = max(suffix[i + 1], r[i] - i + 1);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans = max(ans, r[i] - i + 1 + suffix[r[i] + 1]);
    }
    cout << ans;
}