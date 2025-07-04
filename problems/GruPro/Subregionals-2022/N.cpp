// #define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define printmsg(msg, first, last) \
    cout << msg; \
    for (auto it = first; it != last; it++) { \
        cout << *it << " "; \
    } \
    cout << endl

const i64 INF = (i64)2e18;

template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

/*
K cyclic window
top-L back side
*/

struct top_k_window {
    i64 k;
    set<pair<i64, i64>, less<pair<i64, i64>>> top;
    set<pair<i64, i64>, greater<pair<i64, i64>>> bottom;
    i64 _sum = 0;

    top_k_window(i64 k) {
        this->k = k;
    }

    void add(i64 x, i64 pos){
        if (top.size() < k) {
            top.emplace(x, pos);
            _sum += x;
        } else {  // k > 0
            auto[y, pos2] = *top.begin();
            if (x >= y){  // swap
                top.erase(top.begin());
                top.emplace(x, pos);
                bottom.emplace(y, pos2);
                _sum += x - y;
            } else {
                bottom.emplace(x, pos);
            }
        }
    }
    
    void remove(i64 x, i64 pos){
        auto it = top.find(make_pair(x, pos));
        if (it != top.end()){
            top.erase(it);
            _sum -= x;
            // try to fill
            if (!bottom.empty()){
                auto[y, pos2] = *bottom.begin();
                bottom.erase(bottom.begin());
                top.emplace(y, pos2);
                _sum += y;
            }
        }
        bottom.erase(make_pair(x, pos));
    }

    i64 sum() { return _sum; }
};

void solve(){
    i64 n;
    cin >> n;
    vector<i64> a(n), b(n);
    for (i64 i = 0; i < n; i++) cin >> a[i];
    for (i64 i = 0; i < n; i++) cin >> b[i];

    i64 k, l;
    cin >> k >> l;

    top_k_window win(l);

    i64 k_sum = 0;
    for (i64 i = 0; i < k; i++){
        win.add(b[i], i);
        k_sum += a[i];
    }

    i64 ans = k_sum + win.sum();
    // window is some subarray of size k on cyclic array (array concatenated with itself)
    // that CONTAINS EITHER 0 OR n-1 (otherwise did not start at the edges)

    // move window start to the left (moving over n-1)
    i64 left = k - 1, right = n - 1;
    while (left >= 0){

        k_sum -= a[left];
        win.remove(b[left], left);

        k_sum += a[right];
        win.add(b[right], right);

        ans = max(ans, k_sum + win.sum());
        --left; --right;
    }
    cout << ans << endl;
}

signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}
