#include <bits/stdc++.h>
using namespace std;

#define ALPHABET 256

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
        if (cls[k][i] == cls[k][j]){
            i = (i + (1ll << k)) % n;
            j = (j + (1ll << k)) % n;
            ans += (1ll << k);
        }
    }
    return ans;
}