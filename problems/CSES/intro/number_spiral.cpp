#include <bits/stdc++.h>
using namespace std;

// column contribution:
// row contribution:
//

/*
if x >= y:
    is in last row on x^2 square
    M[x][0] = x^2 if x % 2 == 0 else (x-1)^2 + 1
    if x % 2 == 0: decrement y - 1
    else : increment y - 1
    so
    M[x][y] = x^2 - y + 1 if x % 2 == 0 else (x-1)^2 + y
if y > x:
    is in last column on y^2 square
    M[0][y] = (y-1)^2 + 1 if y % 2 == 0 else y^2
    if y % 2 == 0: increment x - 1
    else : decrement x - 1
    so
    M[x][y] = (y-1)^2 + x if y % 2 == 0 else y^2 - x + 1
*/

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long x, y, ans;
        cin >> x >> y;
        if (x >= y)
        {
            ans = (x % 2 == 0) ? x*x - y + 1 : (x-1)*(x-1) + y;
        } else 
        {
            ans = (y % 2 == 0) ? (y-1)*(y-1) + x : y*y - x + 1;
        }
        cout << ans << '\n';
    }
}