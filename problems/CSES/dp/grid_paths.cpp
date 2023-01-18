#include <bits/stdc++.h>
using namespace std;
#define INF (int)(2e9)
// #define int long long
#define mod (int)(1e9 + 7)
#define vi vector<int>
#define vvi vector<vector<int>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define fi first
#define sec second

int pathcount(vvi& grid, vvi& dp, pii start, pii end, int n){
    if (grid[start.fi][start.sec] != 0 || grid[end.fi][end.sec] != 0){
        // we need both start and end point empty
        return 0;
    }
    else if (start == end){
        return 1; // the empty path, considering that square as empty 
    }
    else if (dp[start.fi][start.sec] != -1){
        return dp[start.fi][start.sec];
    }
    else {
        dp[start.fi][start.sec] = 0;
        if (start.fi + 1 < n && grid[start.fi + 1][start.sec] == 0){
            dp[start.fi][start.sec] = (dp[start.fi][start.sec] % mod + 
                                        pathcount(grid, dp, make_pair(start.fi + 1, start.sec), end, n) % mod
                                        ) % mod;
        }
        if (start.sec + 1 < n && grid[start.fi][start.sec + 1] == 0){
            dp[start.fi][start.sec] = (dp[start.fi][start.sec] % mod + 
                                        pathcount(grid, dp, make_pair(start.fi, start.sec + 1), end, n) % mod
                                        ) % mod;
        }
        return dp[start.fi][start.sec];
    }
}

int main(){
    int n;
    cin >> n;
    vvi grid(n, vi(n, 0));
    char c;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> c;
            if (c != '.') grid[i][j] = 1;
        }
    }
    vvi dp(n, vi(n, -1));
    cout << pathcount(grid, dp, make_pair(0, 0), make_pair(n-1, n-1), n);
}