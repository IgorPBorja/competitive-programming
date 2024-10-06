//#define TESTCASES
 
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

struct Slide{
    map<i64, i64> sums;
    vector<i64> prefs;

    Slide(vector<i64> prefs){
        this->prefs = prefs;
    }

    void remove(i64 i){
        --sums[prefs[i]];
        if (sums[prefs[i]] == 0){
            sums.erase(prefs[i]);
        }
    }

    void insert(i64 i){
        ++sums[prefs[i]];
    }

    i64 minp(){
        return sums.begin()->first;
    }
};

void solve(){
    i64 n, a, b;
    cin >> n >> a >> b;
    vector<i64> arr(n), pref(n + 1);
    pref[0] = 0;
    for (i64 i = 0; i < n; i++){
        cin >> arr[i];
        pref[i + 1] = pref[i] + arr[i];
    }

    Slide min_prefs(pref);
    min_prefs.insert(0);
    i64 max_c = pref[a];
    for (i64 i = a + 1; i <= n; i++){
        // trying to add i - 1 to the mix
        // max window is i - b ... i - 1
        // if i - b - 1 >= 0, then remove pref[i - b - 1]
        if (i - b - 1 >= 0){
            min_prefs.remove(i - b - 1);
        }
        min_prefs.insert(i - a);
        max_c = max(max_c, pref[i] - min_prefs.minp());
    }
    cout << max_c << endl;
}
 
signed main(){
	fastio;
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
