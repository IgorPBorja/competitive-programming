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

void solve(){
    i64 n, _, k;
    cin >> n >> _;
    cin >> k;

    i64 l = 0, r = n - 1;
    // target is pos + 1 - sum[0..pos] =  k
    // if pos + 1 - sum[0..pos] < k, go higher
    // else go lower 
    i64 mid, ans;
    while (l <= r){
        mid = l + (r - l) / 2;
        i64 sum;
        cout << "?" << " " << 1 << " " << mid + 1 << endl;
        cout.flush();

        cin >> sum;
        if (mid + 1 - sum < k){
            l = mid + 1;
        } else if (mid + 1 - sum > k){
            r = mid - 1;
        } else {
            ans = mid;
            r = mid - 1;
        }
    }
    cout << "!" << " " << ans + 1 << endl;
    cout.flush();
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
