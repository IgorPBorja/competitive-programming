// #define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define ALPHABET 256
#define printmsg(msg, first, last) cerr << msg; for (auto it = first; it != last; it++) cout << *it << " "; cout << endl;
#define ASSERT(left,operator,right) { if(!((left) operator (right))){ std::cerr << "ASSERT FAILED: " << #left << #operator << #right << " @ " << __FILE__ << " (" << __LINE__ << "). " << #left << "=" << (left) << "; " << #right << "=" << (right) << std::endl; } }

void csort(vector<int>& p, const vector<int>& classes, int offset){
    const int n = p.size();
    vector<int> cnt(max(ALPHABET, n), 0), ptemp(n);
    for (int i = 0; i < n; i++){
        ++cnt[classes[i]];
    }
    for (int i = 1; i < max(ALPHABET, n); i++){
        cnt[i] += cnt[i - 1];
    }
    // distribute on blocks in reverse order to make sorting stable
    // distribute according to order of k-th element (k=offset)
    for (int i = n - 1; i >= 0; i--){
        int offseted_pos = (p[i] + offset) % n;
        ptemp[--cnt[classes[offseted_pos]]] = p[i];
    }
    swap(ptemp, p);
}

pair<vector<int>, vector<vector<int>>> suffix_array(const string& s){
    int lg = 0;
    string t = s;
    t.push_back('$');
    int n = t.size();
    while ((1ll << lg) < n) ++lg;  // now 2^lg >= n
    vector<int> p(n);
    vector<vector<int>> c(lg + 1, vector<int>(n));
    for (int i = 0; i < n; i++){
        p[i] = i;
        c[0][i] = (int)t[i];
    }
    csort(p, c[0], 0);
    // check offset of size 2^k
    for (int k = 0; k <= lg; k++){
        csort(p, c[k], (1ll << k));  // sort by second, stably
        csort(p, c[k], 0);  // sort by first, stably
        if (k == lg) break;
        // redo equivalence classes
        c[k + 1][p[0]] = 0;  // first element receives class=0
        int cls = 0;
        for (int i = 1; i < n; i++){
            if (
                (c[k][p[i - 1]] < c[k][p[i]])
                || (c[k][(p[i - 1] + (1ll << k)) % n] < c[k][(p[i] + (1ll << k)) % n])
            ){
                ++cls;
            }
            c[k + 1][p[i]] = cls;
        }
    }
    return {p, c};
}

int lcp(int i, int j, const vector<vector<int>>& cls){
    const int n = cls[0].size();
    int lg = 0;
    while ((1ll << lg) < n) ++lg;  // now 2^lg >= n
    int ans = 0;
    for (int k = lg; k >= 0; k--){
        // printf("cls[%d][%d]=%d, cls[%d][%d]=%d\n", k, i, cls[k][i], k, j, cls[k][j]);
        if (cls[k][i] == cls[k][j]){
            i = (i + (1ll << k)) % n;
            j = (j + (1ll << k)) % n;
            ans += (1ll << k);
        }
    }
    return ans;
}

void solve(){
    string s;
    cin >> s;
    const int n = s.size();
    if (n == 1){
        cout << 1 << endl;
        return;
    }
    auto[p, c] = suffix_array(s);
    // printmsg("p=", p.begin(), p.end());
    int64_t substr = n - p[1];  // starting at p[1]
    for (int i = 2; i <= n; i++){
        // the largest common prefix with the previous suffix (which is the most similar suffix already counted)
        // reveals how many substrings starting at i are duplicates
        // p[i]...p[i]+lcp-1 excluded and p[i]+lcp...n-1 included
        // int l = lcp(p[i - 1], p[i], c);
        // cout << "lcp(" << p[i - 1] << "," << p[i] << ")=" << l << endl;
        substr += n - p[i] - lcp(p[i - 1], p[i], c);
    }
    cout << substr << endl;
}

signed main(){
    int t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--) solve();
}