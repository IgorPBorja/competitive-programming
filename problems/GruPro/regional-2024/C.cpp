#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define printmsg(msg, first, last) cerr << msg; for (auto it = first; it != last; it++) cerr << *it << " "; cerr << endl;

const i64 INF = (i64)2e18;

void csort(
    vector<i64>& p,
    const vector<i64>& c,
    i64 offset
){
    const i64 n = p.size();
    vector<i64> ptemp(n), cnt(n + 1); // 0 to n
    for (i64 i = 0; i < n; i++){
        ++cnt[c[i]];
    }
    for (i64 i = 1; i <= n; i++){
        cnt[i] += cnt[i - 1];
    }

    // fill block for p[i] + offset (in reverse order so stable)
    // p[i] = from which position the i-th suffix according to some offset degree comes from?
    for (i64 i = n - 1; i >= 0; i--){
       ptemp[--cnt[c[(p[i] + offset) % n]]] = p[i];
    }
    swap(ptemp, p);
}

pair<vector<i64>, vector<vector<i64>>> suffix_array(const vector<i64>& v){
    const i64 n = v.size();
    // log at most 25
    vector<vector<i64>> c(25, vector<i64>(n + 1));
    vector<i64> p(n + 1);
    for (i64 i = 0; i < n; i++){
        p[i] = i;
        c[0][i] = v[i];
    }
    p[n] = n;
    c[0][n] = 0;
    csort(p, c[0], 0);
    // looking at offset k
    // so [i..i+2k]
    for (i64 k = 1, h = 0; k < 2 * (n + 1); k <<= 1, h++){
        // csort by offseted element
        csort(p, c[h], k);
        // csort by first element (stable)
        csort(p, c[h], 0);
        // redo classes according to block of size 2 * k
        c[h + 1][p[0]] = 0;
        i64 cls = 0;
        for (i64 i = 1; i <= n; i++){
            if (
                (c[h][p[i - 1]] < c[h][p[i]])
                || (c[h][p[i - 1]] == c[h][p[i]] && c[h][(p[i - 1] + k) % (n + 1)] < c[h][(p[i] + k) % (n + 1)])
            ){
                ++cls;
            }
            c[h + 1][p[i]] = cls;
        }
    }
    // remove first class from all
    vector<i64> pf(n);
    vector<vector<i64>> cf(25, vector<i64>(n));
    for (i64 i = 0; i < n; i++) {
        pf[i] = p[i + 1]; // the first comes from sentinel
        for (i64 j = 0; j < 25; j++) cf[j][i] = c[j][i] - 1;  // -1 because of starter cls
    }
    return {pf, cf};
}

i64 lcp(
    const vector<vector<i64>>& c,
    i64 i,
    i64 j
){
    const i64 n = c[0].size();
    i64 lg = 0;
    while ((1ll << lg) < n) ++lg;
    i64 ans = 0;
    for (i64 k = lg; k >= 0 && i < n && j < n; k--){
        if (c[k][i] == c[k][j]){
            ans += (1ll << k);
            i = i + (1ll << k);
            j = j + (1ll << k);
        }
    }
    return ans;
}

void solve(){
    i64 n;
    cin >> n;
    vector<i64> v(n);
    for (i64 i = 0; i < n; i++) {
        cin >> v[i];
    }
    auto[p, c] = suffix_array(v);
    vector<i64> lcp_array(n);
    
    // like a window
    for (i64 i = 0; i + 1 < n; i++){
        lcp_array[i] = lcp(c, p[i], p[i + 1]);
    }
    lcp_array[n - 1] = 0;

    // n * (n + 1) / 2 because of full matches
    i64 num = (n * (n + 1)) / 2, denum = n * n;
    vector<i64> s(n + 1);
    s[n] = 0;
    set<pair<i64, i64>> mins;
    i64 set_sum = 0;
    for (i64 i = n - 1; i >= 0; i--){
        i64 eq_cnt = 1;
        s[i] = s[i + 1];
        while (!mins.empty()){
            auto[m, cnt_m] = *mins.rbegin();
            if (m < lcp_array[i]) break;
            mins.erase(make_pair(m, cnt_m));
            eq_cnt += cnt_m;
            set_sum -= m * cnt_m;
        }
        // the 2 is because of order swap
        s[i] += 2 * set_sum;
        mins.emplace(lcp_array[i], eq_cnt);
        set_sum += lcp_array[i] * eq_cnt;
        // the 2 is because of order swap
        s[i] += 2 * lcp_array[i] * eq_cnt;
    }
    num += s[0];

    i64 d = gcd(num, denum);
    cout << num / d << "/" << denum / d << endl;
}

signed main(){
    int t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--) solve();
}
