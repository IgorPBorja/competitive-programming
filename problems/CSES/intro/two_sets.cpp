#include <bits/stdc++.h>
using namespace std;

/*
1 + ... + n = (n(n+1))/2 = 0 mod 2
iff
4 | n or 4 | n + 1 since mdc(n, n + 1) = 1
CASE 1: n = 0 mod 4
    put pairs (i, n - i) alternately into set 1 and 2

CASE 2: n = 3 mod 4
    put 1,2 in set 1
    put 3 in set 2
    put pairs (i, n - i + 4) alternately into set 1 and 2

obs
CASE n % 4 == 0
    // the i < n + 1 - i conditions guarantees going up to half of the array
CASE n % 4 == 3
    we need reflection in (4,...n)
    so we shift all by -3 , reflect (x |-> n + 1 - x) and shift back
    so we use the pairs (i, n + 1 - 3 - (i - 3) + 3) = (i, n + 4 - i)
    and we adjust the condition to i < n + 4 - i

    --> num < reflection(num)
*/


int main()
{
    int n;
    cin >> n;
    if (n % 4 == 1 || n % 4 == 2)
    {
        cout << "NO";
    } else 
    {
        cout << "YES\n";
        vector<int> s1, s2;
        if (n % 4 == 0)
        {
            for (int i = 1; i < n + 1 - i; i += 2)
            {
                s1.emplace_back(i);
                s1.emplace_back(n + 1 - i);
            }
            for (int i = 2; i < n + 1 - i; i += 2)
            {
                s2.emplace_back(i);
                s2.emplace_back(n + 1 - i);
            }
        }
        else if (n % 4 == 3)
        {
            s1.emplace_back(1);
            s1.emplace_back(2);
            s2.emplace_back(3);
            for (int i = 4; i < n + 4 - i; i += 2)
            {
                s1.emplace_back(i);
                s1.emplace_back(n + 4 - i);
            }
            for (int i = 5; i < n + 4 - i; i += 2)
            {
                s2.emplace_back(i);
                s2.emplace_back(n + 4 - i);
            }
        }
        
        for (vector<int> v: {s1, s2})
        {
            cout << v.size() << '\n';
            for (int x : v)
            {
                cout << x << ' ';
            }
            cout << '\n';
        }
    }
}
