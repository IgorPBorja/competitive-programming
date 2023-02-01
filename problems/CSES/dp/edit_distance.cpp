/*
suppose n <= m and let A[1..n] and B[1..m] be the strings
let dp[i][j] be the minimum number of operations to turn a substring of size i of B ending at j into A
(INF if j < i).
Then

dp[i+1][j] = INF if j < i+1
            min(dp[i+1][j], dp[i][j-1] + (B[j] == A[i+1]) ? 0 : 1)  

loop i
    loop j

then edit(A, B) = min(j){dp[n][j]} + m - n

base case: dp[n][n] = diff(A, B[1..n]) 
*/
#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;

int diff(string& A, string& B){
    /*needs |s1| <= |s2| */
    int n = A.size(), m = B.size();
    if (n > m){
        return diff(B, A);
    }
    int dp[n][m];
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            dp[i][j] = INF;
        }
    }

    // base cases: dp[0][j]
    for (int j = 0; j < m; j++){
        if (B[j] == A[0]){
            dp[0][j] = 0;
        } else {
            dp[0][j] = 1;
        }
    }

    for (int i = 1; i < n; i++){
        // dp[i][j] =  turn substring of size i + 1 of B ending at j into A[0...i]
        for (int j = i; j < m; j++){
            if (A[i] != B[j]){
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
            } else {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);                
            }
        }
    }

    // ans = min(j)dp[n-1][j] + m - n
    int ans = INF;
    for (int j = 0; j < m; j++){
        ans = min(ans, dp[n-1][j]);
    }
    return ans + m - n;
}

int main(){
    string s1, s2;
    cin >> s1 >> s2;
    cout << diff(s1, s2);
}