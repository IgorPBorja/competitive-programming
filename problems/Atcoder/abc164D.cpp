#include <bits/stdc++.h>
using namespace std;

int main()
{

    int m[2019];
    for (int i = 0; i < 2019; i++) m[i] = 0;
    string s;
    getline(cin, s);


    int exp_factor[(int)s.size()];
    exp_factor[0] = 1;
    for (int i = 1; i < (int)s.size(); i++)
    {
        exp_factor[i] = (exp_factor[i-1] * 202) % 2019; // 202 = 10^-1 mod 2019
    }

    int r = 0;
    ++m[0]; // empty seq
    for (int i = 0; i < (int)s.size(); i++)
    {
        r = (r * 10 + (s[i] - '0')) % 2019;
        ++m[(r * exp_factor[i]) % 2019];
    }

    long long res = 0;
    for (int i = 0; i < 2019; i++)
    {
        res += ( (long long)(m[i]) * ((long long)(m[i]) - 1) ) / 2; 
    }
    cout << res;
}