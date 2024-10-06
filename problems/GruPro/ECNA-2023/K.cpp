#include<bits/stdc++.h>

using namespace std;
#define int long long
#define all(a) a.begin(),a.end()

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string>a(n);
    for(auto &i:a)cin >> i;

    int ans = 0;
    map<tuple<string, int, int>,int> mp;
    for(int i = 0; i < n; i++){
        for(int j = i+1; j < n; j++){
            string s = a[i],t = a[j];
            if (s.size() != t.size()) continue;
            if (s > t) swap(s, t);

            int idx = -1, ok = 1, cnt= (s[s.size() - 1] != t[s.size() - 1]);
            for(int k =0; k < s.size()-1; k++){
                if(s[k] != t[k] && s[k+1] != t[k+1]){
                    if(idx != -1)ok = 0;

                    idx = k;
                }

                cnt += (s[k] != t[k]);
            }

            if(idx ==-1 or !ok or cnt > 2)continue;

            string clue = s.substr(idx,2) + "/" + t.substr(idx,2);
            // cout << clue << endl;
            ++mp[tuple<string, int, int>(clue, idx, s.size())];
        }
    }

    for(auto it:mp) ans += (it.second == 1);

    cout << ans << endl;
    return 0;
}