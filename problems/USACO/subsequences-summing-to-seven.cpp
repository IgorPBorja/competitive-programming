#include <bits/stdc++.h>
using namespace std;

// first[i] = first index j st sum(1..j-1)a[k] = i mod 7
// last[i] = last index j st sum(1..j-1)a[k] = i mod 7

int main()
{
    #define INF int(2e9)
    freopen("div7.in", "r", stdin);
    int n;
    cin >> n;
    int first[7], last[7];
    for (int i = 0; i < 7; i++)
    {
        first[i] = INF;
        last[i] = 0;
    } 
    first[0] = 0;     

    int s = 0, a;
    for (int i = 1; i < n; i++)
    {
        cin >> a;
        s = (s + (a % 7)) % 7;
        if (first[s] == INF)
        {
            first[s] = i;
        }
        last[s] = i;
    }

    int m = 0;
    for (int rem = 0; rem < 7; rem++)
    {
        m = max(m, last[rem] - first[rem]);
    }

    freopen("div7.out", "w", stdout);
    cout << m;
}