//#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define INF (int)(2e9)
//#define int long long
/*
#define vi vector<int>
#define vvi vector<vector<int>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define fi first
#define sec second
*/
int remove_digits(int n, int dp[]){
    if (n == 0){
        return 0;
    }
    else if (dp[n] != INF){
        return dp[n];
    } 
    else {
        int curr = n;
        while (curr > 0){
            int d = curr % 10;
            if (d != 0){
                dp[n] = min(1 + remove_digits(n - d, dp), dp[n]);
            } // if we allow d == 0 we get into infinite loop when n = 0 mod 10
            curr = curr / 10;
        }
        return dp[n];
    }
}

int main()
{
    int n;
    cin >> n;
    int dp[n+1];
    for (int i = 0; i < n + 1; i++){
        dp[i] = INF;
    } 
    cout << remove_digits(n, dp);
}