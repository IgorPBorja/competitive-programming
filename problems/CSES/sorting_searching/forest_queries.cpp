#include <bits/stdc++.h>
using namespace std;
#define vvi vector<vector<int>>

vvi psmatrix(vvi& a, int n, int m){
    vvi p(n, vector<int>(m, 0)); // O(mn)
    for (int i = 0; i < n; i++){ // O(mn)
        for (int j = 0; j < m; j++){
            p[i][j] += a[i][j];
            if (i > 0){
                p[i][j] += p[i-1][j];
            } 
            if (j > 0){
                p[i][j] += p[i][j-1];
            } 
            if (i > 0 && j > 0){
                p[i][j] -= p[i-1][j-1];
            }
        }
    }
    return p;
}

int query_subrect_sum(vvi& p, 
                    int i0, int j0,
                    int i1, int j1,
                    int n, int m){
    assert(0 <= i0 && i0 <= i1 && i1 < n);
    assert(0 <= j0 && j0 <= j1 && j1 < m);
    
    // queries an inclusive range
    int q = p[i1][j1];
    if (i0 > 0){
        // remove top 
        q -= p[i0 - 1][j1];
    }
    if (j0 > 0){
        // remove left
        q -= p[i1][j0 - 1];
    }
    if (i0 > 0 && j0 > 0){
        // compensate double removal of square 
        q += p[i0 - 1][j0 - 1];
    }
    return q;
}

int main(){
    int n, q, i0, j0, i1, j1;
    cin >> n >> q;
    vvi a(n, vector<int>(n, 0)); // O(n^2)
    char c;
    // O(n^2)
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> c;
            if (c == '*'){
                a[i][j] = 1;
            }
        }
    }
    // O(q)
    vvi p = psmatrix(a, n, n);
    for (int i = 0; i < q; i++){
        cin >> i0 >> j0 >> i1 >> j1;
        // adjust for -----1-INDEXING------
        int ans = query_subrect_sum(p, i0 - 1, j0 - 1, i1 - 1, j1 - 1, n, n);
        cout << ans << '\n';
    }
}