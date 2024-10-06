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
    
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
    
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
    
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
    out << x.first << " " << x.second;
    return out;
}
    
vector<vector<i64>> merge(const vector<vector<i64>> bits, const i64 i){
    // guarantee: number of 1s is even ==> merge always possible
    const i64 n = bits[0].size();
    vector<vector<i64>> new_bits(30);
    
    for (i64 k = 0; k < 30; k++){
        new_bits[k].emplace_back(bits[k][0]);
    }
    bool paired = (bits[i][0] == 0);
    for (i64 j = 1; j < n; j++){
        if (paired){
            for (i64 k = 0; k < 30; k++){
                new_bits[k].emplace_back(bits[k][j]);
            }
            if (bits[i][j] == 1) paired = false;
        } else {
            // XOR merge
            if (bits[i][j] == 1) paired = true;
            for (i64 k = 0; k < 30; k++){
                new_bits[k][new_bits[k].size() - 1] ^= bits[k][j];
            }
        }
    }
    return new_bits;
}
    
void solve(){
    i64 n, x, a;
    
    cin >> n;
    vector<i64> bits_x(30);
    vector<vector<i64>> bits(30, vector<i64>(n));
    
    cin >> x;
    for (i64 i = 0; i < 30; i++){
        bits_x[30 - 1 - i] = x % 2;
        x /= 2;
    }
    
    for (i64 j = 0; j < n; j++){
        cin >> a;
        for (i64 i = 0; i < 30; i++){
            bits[30 - 1 - i][j] = a % 2;
            a /= 2;
        }
    }
    
    i64 forced_ans = -1;
    
    for (i64 i = 0; i < 30; i++){
        // bit i
        
        // OR is only 0 iff each XOR is 0 iff each subsegment has a
        // even amount of 1s
        i64 cnt1 = 0;
        for (i64 j = 0; j < (i64)bits.size(); j++) cnt1 += bits[i][j];
    
        // partition does not matter, will always have bit i <= bit i from x
        // and will only have necesarily bit i of OR == 0 (<) iff all bits are 0, because otherwise can use unit subsegments
        if (bits_x[i] == 1){
            if (cnt1 % 2 == 0){
                // can force answer w/merge
                auto new_bits = merge(bits, i);
                forced_ans = max(forced_ans, (i64)new_bits[0].size());
            } else {
                // any partition will have bit i == 1
                continue;
            }
        }
        else {
            if (cnt1 % 2 == 1){
                // is odd -> will always have odd subsegment -> OR is 1 always
                cout << forced_ans << endl;
                return;
            } else {
                // is even
                // try to merge pairs
                bits = merge(bits, i);
            }
        }
    }
    cout << max(forced_ans, (i64)bits[0].size()) << endl;
}
    
signed main(){
    fastio;
    //freopen("in", "r", stdin);
    int t;
#ifdef TESTCASES
    cin >> t;
#else
    t = 1;
#endif
    while (t--){
        solve();
    }
}