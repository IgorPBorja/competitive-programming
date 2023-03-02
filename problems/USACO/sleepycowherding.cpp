#include <bits/stdc++.h>
using namespace std;

/*
*/

int main()
{
    // for USACO judge
    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);

    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    sort(a, a + n); // increasing order

    if (a[n-2] - a[0] == n - 2 && a[n-1] - a[n-2] > 2)
    {
        cout << 2 << '\n';
        cout << a[n - 1] - a[0] + 2 - n - min(a[1] - a[0], a[n - 1] - a[n - 2]) << '\n';
        return 0;
    } 
    if (a[n-1] - a[1] == n - 2 && a[1] - a[0] > 2)
    {
        cout << 2 << '\n';
        cout << a[n - 1] - a[0] + 2 - n - min(a[1] - a[0], a[n - 1] - a[n - 2]) << '\n';
        return 0;
    }
    int j = 0;
    int ans = 2e9;
    for (int i = 0; i < n; i++){
        while (j + 1 < n && a[j + 1] - a[i] < n)
        {
            ++j;
        }
        ans = min(ans, n + i - j - 1);
    }
    cout << ans << '\n';

    cout << a[n-1] - a[0]+ 2 - n - min(a[1] - a[0], a[n-1] - a[n-2]) << '\n';
}
