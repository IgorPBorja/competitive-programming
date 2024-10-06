#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t


signed main(){
    string s;
    cin >> s;
    i64 sum = 0;
    for (i64 i = 0; i < s.size(); i++){
        sum = (sum + (s[i] - '0')) % 2;
    }
    if (sum == 0){
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}