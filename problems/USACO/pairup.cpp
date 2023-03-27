#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("pairup.in", "r", stdin);
    freopen("pairup.out", "w", stdout);
    int n;
    cin >> n;
    pair<int, int> a[n];
    int x, y;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        a[i] = make_pair(y, x);
    }
    sort(a, a + n);
    
    int l = 0, r = n - 1;
    int ans = 0, delta; // does not overflow since a[l].second + a[r].second <= 1e9 + 1e9
    while (l <= r)
    {
        ans = max(ans, a[l].first + a[r].first);
        if (l != r)
        {
            delta = min(a[l].second, a[r].second); // delta pairs from l and r pos
        } else {
            delta = a[l].second/2;
        }
        a[l].second -= delta;
        a[r].second -= delta;
        if (a[l].second == 0) ++l;
        if (a[r].second == 0) --r;
    }
    cout << ans;
}