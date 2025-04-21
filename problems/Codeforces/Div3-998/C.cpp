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
    i64 n, k;
    cin >> n >> k;

    vector<i64> cnt(2 * n + 1, 0);
    for (i64 i = 0; i < n; i++){
        i64 x;
        cin >> x;
        ++cnt[x];
    }
    i64 score = 0;
    for (i64 i = 0; i < k - i; i++){
        score += min(cnt[i], cnt[k - i]);
    }
    // trying k/2
    if (k % 2 == 0){
        score += cnt[k / 2] / 2;
    }
    cout << score << endl;
}

signed main(){
    fastio;
    int t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--) solve();
}