#define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'

#define i32 int32_t
#define i64 int64_t
#define i128 int128_t

template <typename ForwardIterator>
void print(ForwardIterator itr, int n, string sep=" ")
{
    for (int i = 0; i < n; i++)
    {
        cout << *itr << sep;
        ++itr;
    }
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> v){
    for (T x: v){
        cout << x << " ";
    }
    return os;
}

template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> v){
    cout << "(" << v.first << ", " << v.second << ")";
    return os;
}

vector<vector<i64>> rotate(vector<vector<i64>> m){
    vector<vector<i64>> m2 = m;
    m2[0][0] = m[1][0];
    m2[0][1] = m[0][0];
    m2[1][0] = m[1][1];
    m2[1][1] = m[0][1];
    return m2;
}

bool ok(vector<vector<i64>>& m){
    return (
        (m[0][0] < m[0][1])
        && 
        (m[1][0] < m[1][1])
        &&
        (m[0][0] < m[1][0])
        &&
        (m[0][1] < m[1][1])
    );
}

void solve(){
    vector<vector<i64>> m(2, vector<i64>(2));
    for (int i = 0; i < 2; i++){
        for (int j = 0; j < 2; j++){
            cin >> m[i][j];
        }
    }
    vector<vector<i64>> rot = m;
    for (int i = 0; i < 4; i++){
        rot = rotate(rot);
        if (ok(rot)){
            cout << "YES" << endl;
            return;
        }
    }
    cout << "NO" << endl;
}

int main(){
#ifdef TESTCASES
    int t;
    cin >> t;
    while (t--){
        solve();
    }
#else
    solve()
#endif
    fastio;
}
