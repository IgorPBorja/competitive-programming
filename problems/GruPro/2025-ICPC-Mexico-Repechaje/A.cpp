#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define i64 int64_t

string build_sorted(const string& s){
    vector<i64> freq(26, 0);
    for (i64 j = 0; j < (i64)s.size(); j++){
        ++freq[s[j] - 'a'];
    }
    string t = "";
    t.reserve(s.size());
    for (i64 j = 0; j < 26; j++){
        for (i64 _ = 0; _ < freq[j]; _++) t.push_back((char)('a' + j));
    }
    return t;
}

signed main(){
    fastio;
    i64 n;
    cin >> n;
    vector<string> s(n);
    map<string, string> idx;
    vector<pair<string, string>> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> s[i];
        a[i] = make_pair(build_sorted(s[i]), s[i]);
    }
    sort(a.begin(), a.end());

    i64 q;
    cin >> q;
    for (i64 i = 0; i < q; i++){
        string t;
        cin >> t;
        auto x = make_pair(build_sorted(t), t);
        i64 idx = upper_bound(a.begin(), a.end(), x) - a.begin();
        // 0..idx-1 
        cout << idx << endl;
    }
}