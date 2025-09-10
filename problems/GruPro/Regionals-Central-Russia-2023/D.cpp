// we want fast LCS between s and reverse(comp(s))
// we can do that with suffix-array

#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define all(v) v.begin(),v.end()
#define print(msg, v) cerr << msg; for(auto x: v) cerr << x << " "; cerr << endl

void bucket_sort_by_offset(vector<i64>& p, const vector<i64>& cls, i64 offset){
    // TODO
    const i64 n = p.size();
    vector<i64> new_p(n);
    vector<i64> bucket_last_pos(max((i64)256, n));
    for (i64 i = 0; i < n; i++){
        ++bucket_last_pos[cls[i]];
    }
    for (i64 i = 1; i < max((i64)256, n); i++){
        bucket_last_pos[i] += bucket_last_pos[i - 1];
    }
    // backwards on p-induced sort to guarantee stable sort
    for (i64 i = n - 1; i >= 0; i--){
        const i64 c = cls[(p[i] + offset) % n];
        new_p[--bucket_last_pos[c]] = p[i];
    }
    swap(new_p, p);
}

pair<vector<i64>, vector<vector<i64>>> suffix_array(string s){
    s.push_back('#');

    const i64 n = s.size();
    i64 logN = 0;
    while ((1ll << logN) < n) ++logN;  // 2^logN >= n

    vector<i64> p(n);
    iota(all(p), 0);
    vector<vector<i64>> c(logN + 1, vector<i64>(n));
    for (i64 i = 0; i < n; i++){
        c[0][i] = s[i];  // use ascii code
    }

    // 2^k classes, up to first k s.t 2^k >= n
    for (i64 k = 1; k <= logN; k++){
        // print("for k=" << k << " p=", p);
        bucket_sort_by_offset(p, c[k - 1], (1ll << (k - 1)));
        // cerr << "bucket sort 1 ok" << endl;
        // print("for k=" << k << " p=", p);
        bucket_sort_by_offset(p, c[k - 1], 0);
        // cerr << "bucket sort 2 ok" << endl;
        // print("for k=" << k << " p=", p);

        // for compressed comparison
        auto get_pair = [&c, n, k](i64 i){
            return make_pair(c[k - 1][i], c[k - 1][(i + (1ll << (k - 1))) % n]);
        };

        i64 cur_cls = 0;
        c[k][p[0]] = cur_cls;
        for (i64 i = 1; i < n; i++){
            if (get_pair(p[i]) > get_pair(p[i - 1])) ++cur_cls;  // transition
            c[k][p[i]] = cur_cls;
        }
    }
    return {p, c};
}

i64 lcp(i64 i, i64 j, const vector<vector<i64>>& c){
    const i64 LOGN = c.size(), n = c[0].size();
    i64 ans = 0;
    for (i64 k = LOGN - 1; k >= 0; k--){
        if (c[k][i] == c[k][j]){
            i = (i + (1ll << k)) % n;
            j = (j + (1ll << k)) % n;
            ans += (1ll << k);
        }
    }
    return ans;
}

vector<i64> lcp_array(const vector<i64>& p, const vector<vector<i64>>& c){
    const i64 n = p.size();
    vector<i64> a(n - 1); // a[i] = lcp(p[i], p[i + 1])
    for (i64 i = 0; i + 1 < n; i++){
        a[i] = lcp(p[i], p[i + 1], c);
    }
    return a;
}

signed main(){
    auto transform = [](string s){
        string t;
        for (char c: s){
            if (c == 'A'){
                t.push_back('T');
            } else if (c == 'T'){
                t.push_back('A');
            } else if (c == 'G'){
                t.push_back('C');
            } else {
                t.push_back('G');
            }
        }
        reverse(all(t));
        return t;
    };

    string s;
    cin >> s;
    string t = transform(s);
    string combined = s + "$" + t;  // NOTE: different sentinel than the final one, but larger
    // cerr << "base ok" << endl;
    auto[p, c] = suffix_array(combined);
    // cerr << "suffix array ok" << endl;
    auto a = lcp_array(p, c);
    // cerr << "lcp array ok" << endl;

    // we want lcs of s and t
    i64 lcs = 0;
    i64 s_idx = -1;
    const i64 n = s.size();
    for (i64 i = 0; i + 1 < (i64)p.size(); i++){
        if (min(p[i], p[i + 1]) < n && max(p[i], p[i + 1]) > n){
            // one in s, another in t. Note that max(p[i], p[i+1]) can't be last sentinel char
            if (a[i] > lcs){
                lcs = a[i];
                s_idx = min(p[i], p[i + 1]);
            }
        }
    }
    cout << lcs << endl;
    for (i64 i = 0; i < lcs; i++){
        cout << s[s_idx + i];
    }
    cout << endl;
}
