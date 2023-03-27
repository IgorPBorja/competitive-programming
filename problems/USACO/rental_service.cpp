#include <bits/stdc++.h>
using namespace std;
#define int long long

int main()
{
    int n, m, r;
    cin >> n >> m >> r;

    int c[n], k[r];
    pair<int, int> s[m];

    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < m; i++)
    {
        cin >> s[i].second >> s[i].first; // q_i, p_i
    }
    for (int i = 0; i < r; i++) cin >> k[i];
    sort(s, s + m, [](pair<int ,int> a, pair<int, int> b){return a > b});
    sort(k, k + r, [](int a, int b){return a > b});

    int prefix_q[m + 1], prefix_prod[m + 1];
    prefix_q[0] = 0; prefix_prod[0] = 0;
    prefix_q[1] = s[1].second;
    prefix_prod[1] = s[1].first * s[1].second;
    for (int i = 1; i < m; i++)
    {
        prefix_q[i] = prefix_q[i - 1] + s[i].second;
        prefix_prod[i] = prefix_prod[i - 1] + s[i].first * s[i].second;
    }

    int sptr = 0, kptr = 0;
    int discard_index = 0;
    int t = 0;
    for (int i = 0; i < n; i++)
    {
        // bin search for index of max index that you can go
        // before running out
        int lo = sptr, hi = m - 1, ans = sptr - 1;
        while (lo <= hi)
        {
            int mid = lo + (hi - lo)/2;
            if (prefix_q[mid] - prefix_q[discard_index] > c[i] - )
            {
                hi = mid - 1;
            } else 
            {
                ans = mid;
                lo = mid + 1;
            }
        }
        // did/can move move
        if (ans >= sptr)
        {
            if (kptr >= r || prefix_pq)
            sptr = ans + 1;
            discard = prefix_q[ans];
        }
    }
    cout << t << '\n';
}