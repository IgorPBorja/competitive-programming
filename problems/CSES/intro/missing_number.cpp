#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, a;
    cin >> n;
    bool b[n];
    for (int i = 0; i < n; i++)
    {
        b[i] = false;
    }
    for (int i = 0; i < n - 1; i++)
    {
        cin >> a;
        b[a - 1] = true;
    }
    for (int i = 0; i < n; i++)
    {
        if (!b[i])
        {
            cout << i + 1;
        }
    }
}