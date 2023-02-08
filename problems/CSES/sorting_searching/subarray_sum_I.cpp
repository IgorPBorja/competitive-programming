#include <bits/stdc++.h>
using namespace std;

/*
sliding window
*/

int main()
{
    int n, x;
    cin >> n >> x;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int s = 0, cnt = 0;
    int right = -1; // last index of subarray
    for (int left = 0; left < n; left++)
    {
        while (s + a[right + 1] <= x)
        {
            s += a[right + 1];
            ++right;
        }
        // now we have the closest sum (from below) to x as possible
        if (s == x)
        {
            ++cnt;
        }
        s -= a[left]; // slide to right
    }
    cout << cnt;
}