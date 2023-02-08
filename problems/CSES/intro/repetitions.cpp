#include <bits/stdc++.h>
using namespace std;

int main()
{
    int rep_count = 0, ans = 0;
    string s;
    getline(cin, s);
    for (int i = 0; i < (int)s.size(); i++)
    {
        if (i == 0 || s[i] == s[i-1])
        {
            ++rep_count;
        } else{
            ans = max(ans, rep_count);
            rep_count = 1; // new sequence
        }
    }
    // in case all string is the same char
    cout << max(rep_count, ans);
}