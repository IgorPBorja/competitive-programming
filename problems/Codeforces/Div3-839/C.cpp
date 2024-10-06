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

void solve(){
    i64 n, k;
    cin >> k >> n;
    i64 a[k];
    i64 diff = 1;
    a[0] = 1;
    for (i64 i = 1; i < k; i++){
        i64 pred = a[i - 1] + diff;
        // remains: a[i+1]...a[k-1] ==> k-i-1, after this
        // so pred + k - i - 1 <= n
        if (pred + k - i - 1 <= n){
            a[i] = pred;
            ++diff;
        } else {
            a[i] = a[i - 1] + 1;
        }
    }
    for (i64 i = 0; i < k; i++){
        cout << a[i] << " ";
    }
    cout << endl;
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
