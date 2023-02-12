#include <bits/stdc++.h>
using namespace std;

int bsearch(int a[], int n, int val)
{
    int lo = 0, hi = n - 1; 
    while (lo <= hi)
    {
        int mid = lo + (hi - lo)/2;
        if (val == a[mid])
        {
            return mid;
        } else if (val < a[mid])
        {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return -1;
}

void coordinate_compress(pair<int, int> times[], int n)
{
    // there are 2n distinct values
    int t[2*n];
    for (int i = 0; i < n; i++)
    {
        t[2*i] = times[i].first;
        t[2*i + 1] = times[i].second;
    }
    sort(t, t + 2*n);
    for (int i = 0; i < n; i++)
    {
        int new_start = bsearch(t, 2*n, times[i].first);
        times[i].first = new_start;
        int new_end = bsearch(t, 2*n, times[i].second);
        times[i].second = new_end;
    }
}

int main()
{
    int n;
    cin >> n;
    pair<int, int> times[n];
    for (int i = 0; i < n; i++)
    {
        cin >> times[i].first >> times[i].second;
    }   
    coordinate_compress(times, n);

    int people_cnt[2*n];
    for (int i = 0; i < 2*n; i++) people_cnt[i] = 0;

    for (int i = 0; i < n; i++)
    {
        ++people_cnt[times[i].first];
        if (times[i].second < 2*n - 1)
        {
            --people_cnt[times[i].second + 1];
        }
    }
    // prefix sum
    for (int i = 0; i < 2*n - 1; i++)
    {
        people_cnt[i + 1] += people_cnt[i];
    }

    int ans = 0;
    for (int i = 0; i < 2*n; i++)
    {
        ans = max(ans, people_cnt[i]);
    }
    cout << ans;
}