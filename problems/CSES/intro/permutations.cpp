#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << 1;
        return 0;
    }
    if (1 < n && n <= 3)
    {
        cout << "NO SOLUTION";
        return 0;
    }
    else 
    {
        int k = n/2;
        for (int i = 0; i < n / 2; i++)
        {
            cout << k << ' ' << k + n/2 << ' ';
            k--;
        }
        if (n % 2 == 1)
        {
            cout << n;
        }
    }
}