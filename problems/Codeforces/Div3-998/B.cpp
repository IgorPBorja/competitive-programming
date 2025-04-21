#define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define i64 int64_t
#define printmsg(msg, first, last) cerr << msg; for(auto it = first; it != last; it++) cerr << *it << " "; cerr << endl
#define endl "\n"

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, pair<T, U> p){
    os << p.first << "," << p.second;
    return os;
}

void solve(){
    i64 n, m;
    cin >> n >> m;
    vector<vector<i64>> a(n, vector<i64>(m));
    vector<pair<i64, i64>> firsts;
    for (i64 i = 0; i < n; i++){
        for (i64 j = 0; j < m; j++){
            cin >> a[i][j];
        }
        sort(a[i].begin(), a[i].end());
        firsts.emplace_back(a[i][0], i);  // smallest
    }
    sort(firsts.begin(), firsts.end());
    // printmsg("firsts=", firsts.begin(), firsts.end());
    vector<i64> p;
    for (auto[_, i]: firsts){
        p.emplace_back(i);
    }
    // printmsg("p=", p.begin(), p.end());
    // for each j check sorted
    bool global_is_sorted = true;
    i64 turn_end = a[p.back()][0];
    for (i64 j = 1; j < m; j++){
        bool is_sorted = turn_end < a[p[0]][j];
        for (i64 i = 0; i + 1 < n; i++){
            is_sorted &= a[p[i]][j] < a[p[i + 1]][j];
        }
        global_is_sorted &= is_sorted;
        turn_end = a[p.back()][j];
    }
    if (global_is_sorted){
        for (i64 x: p){
            cout << x + 1 << " ";
        }
        cout << endl;
    } else {
        cout << -1 << endl;
    }
}

signed main(){
    fastio;
    int t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--) solve();
}