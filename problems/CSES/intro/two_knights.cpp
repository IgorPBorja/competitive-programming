#include <bits/stdc++.h>
using namespace std;

/*
offsets:
all combinations of (+-1,+-2) and (+-2, +-1)

given an offset, the number of the squares from where the offset can be applied is
dx > 0, dy > 0:
    #{x <= n - 1, y <= n - 2} = #{x <= n - 2, y <= n-1} = (n-1)(n-2)
dx > 0, dy < 0
    #{x <= n - 1, y >= 2 + 1} = #{x <= n - 2, y >= 1 + 1} = (n-1)(n-2) 
...
in all cases, it is (n-1)(n-2)

so there are 8*(n-1)(n-2) knight movements

==> there are moves/2 = 4(n-1)(n-2) knight pairs

so there are choose(n^2, 2) - 4(n-1)(n-2) =  [ n^2(n^2-1) - 8(n-1)(n-2) ] / 2
= (n-1)[n^2(n+1) - 8(n-2)] / 2 free pairs
*/

int main()
{
    int k;
    cin >> k;
    for (long long i = 1; i <= k; i++)
    {
        // long long -> avoid overflow
        cout << (i - 1) * ( (i*i*(i + 1) - 8*(i - 2)) / 2 ) << '\n';
    }
}