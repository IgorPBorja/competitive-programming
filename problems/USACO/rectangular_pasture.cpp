#include <bits/stdc++.h>
using namespace std;

int bsearch(int val, int x[], int n)
{
    int lo = 0, hi = n - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (val == x[mid])
        {
            return mid;
        }
        else if (val < x[mid])
        {
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }
    return -1;
}

void swap(int &a, int &b)
{
    int temp;
    temp = max(a, b);
    a = min(a, b);
    b = temp;
}

int main()
{
    int n;
    cin >> n;
    int xs[n], ys[n];
    pair<int, int> points[n];
    for (int i = 0; i < n; i++)
    {
        cin >> points[i].first >> points[i].second;
        xs[i] = points[i].first;
        ys[i] = points[i].second;
    }
    sort(xs, xs + n);
    sort(ys, ys + n);

    int ps[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            ps[i][j] = 0;
        }
    }

    // compressing
    for (int i = 0; i < n; i++)
    {
        int ix = bsearch(points[i].first, xs, n);
        int iy = bsearch(points[i].second, ys, n);
        points[i].first = ix;
        points[i].second = iy;
        ++ps[ix][iy];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j > 0)
                ps[i][j] += ps[i][j - 1];
            if (i > 0)
                ps[i][j] += ps[i - 1][j];
            if (i > 0 && j > 0)
                ps[i][j] -= ps[i - 1][j - 1];
        }
    }

    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            int i0 = points[i].first;
            int j0 = points[i].second;
            int i1 = points[j].first;
            int j1 = points[j].second;
            swap(i0, i1);
            swap(j0, j1);

            int a = (long long)(ps[i1][n - 1] - ps[i0][n - 1]) - (long long)(ps[i1][j1] - ps[i0][j1]);
            int b = 0;
            if (j0 > 0)
            {

                b += (long long)(ps[i1][j0 - 1] - ps[i0][j0 - 1]);
            }
            ans += (a + 1) * (b + 1);
        }
    }
    cout << ans + n + 1;
}