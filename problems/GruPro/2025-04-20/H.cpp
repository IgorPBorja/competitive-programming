// #define TESTCASES
// #define DEBUG
 
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define printgraph(msg, G) cout << msg << endl; for (u64 u = 0; u < G.size(); u++) { printmsg("G[" << u << "]=", G[u].begin(), G[u].end()) };
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

/*
ans = sum(b) 2^b * sum(l) sum(r) [(count(a_i: bit b of a_i is 1, l <= i <= r)) mod 2] * (r - l + 1)

Lets solve for each bit b
if p[0],...,p[k-1] are the active positions of bit b in increasing order, then we will sum
p[i]-p[i+2d]+1 for each 0<=i<=k-1 and 0<=d<=floor((k-1-i)/2)

So each position that comes after p[j-1] (strictly) and before or at p[j] will appear with a minus sign for
    p[j] through p[j+1]-1
    p[j+2] through p[j+3]-1
    ...

    So delta[j] + delta[j+2] + ... + delta[j+floor((k-1-j)/2)]
    NOTE: no positions after p[k-1] will appear as left endpoint
And each position that comes after or on p[j] and before p[j+1] (strictly) will appear with a plus sign for
    p[j-1]+1 through p[j]
    ...
    So delta[j-1] + delta[j-3] + ... + delta[j-1-2*floor((j-1)/2)]
    NOTE: no positions before p[0] will appear as right endpoint
We can iterate over each position, its fine since it is O(n) repeated O(log n)

The +1 will appear for pairs (0,0), (0,2), ..., (0, 2 * floor((k-1)/2))) ==> floor((k-1)/2) + 1 pairs = floor((k+1)/2)
then (1,1), (1,3), ..., (1, 1+2*floor((k-2)/2))) ==> floor((k-2)/2) = floor(k/2) pairs
...
(k-1, k-1) for floor(2/2) = 1 pairs
We can use prefix sum for that.
*/

const i64 MOD = 998244353;
const i64 B = 30;  // 2^30 > 10^9 so we have at most 30 active bits

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++) cin >> a[i];

    vector<i64> active[B];
    for (i64 i = 0; i < B; i++){
        // active[i].emplace_back(-1);
        for (i64 j = 0; j < n; j++){
            if (a[j] & (1ll << i)) active[i].emplace_back(j);
        }
    }
    // printmsg("pos first bit", active[0].begin(), active[0].end());
    // printmsg("pos second bit", active[1].begin(), active[1].end());

    i64 pref_div2[n + 2];
    for (i64 i = 0; i <= n + 1; i++) pref_div2[i] = i / 2;
    for (i64 i = 1; i <= n + 1; i++) pref_div2[i] += pref_div2[i-1];

    i64 total = 0;
    for (i64 i = 0; i < B; i++){
        i64 power = (1ll << i) % MOD;  // 2^i <= 2^30
        i64 bit_total = 0;
        const i64 k = active[i].size();  // NOTE -1
        if (k == 0) continue;

        i64 delta_pref[k - 1], delta_suf[k - 1];
        for (i64 j = 0; j < k - 1; j++){
            delta_pref[j] = active[i][j+1] - active[i][j];
            delta_suf[j] = active[i][j+1] - active[i][j];
        }
        for (i64 j = 2; j < k - 1; j++){
            delta_pref[j] += delta_pref[j - 2];
        }
        for (i64 j = k - 4; j >= 0; j--){
            delta_suf[j] += delta_suf[j + 2];
        }
        // printmsg("delta_pref=", delta_pref, delta_pref + k - 1);
        // printmsg("delta_suf=", delta_suf, delta_suf + k - 1);
        i64 j = -1, j2 = 0;
        for (i64 idx = 0; idx < n; idx++){
            i64 contrib = 0;
            // p[j] is behind or at idx  --> helps with +
            // p[j2] is after or at idx  --> helps with -
            if (j + 1 < k && idx == active[i][j+1]) ++j;
            if (idx - 1 == active[i][j2]) ++j2;
            // minus sign for delta[j2] + delta[j2+2] + ... + delta[j2+floor((k-1-j)/2)]
            // plus sign for delta[j-1] + delta[j-3] + ... + delta[j-1-2*floor((j-1)/2)]
            if (j2 < k - 1){
                // -1 excludes itself
                contrib = (contrib + MOD - (delta_suf[j2] - 1)) % MOD;
            } else {
                // no one after it
            }
            // -1 excludes itself
            if (j > 0) contrib = (contrib + delta_pref[j - 1] - 1) % MOD;
            if (j == 0){
                // no one before it --> grab 0...p[0]-1
                contrib = (contrib + active[i][0]) % MOD;
            }
            // cout << "idx=" << idx << " contrib=" << contrib << endl;
            bit_total = (bit_total + power * contrib) % MOD;
        }
        bit_total = (bit_total + pref_div2[k + 1]) % MOD;
        total = (total + bit_total) % MOD;
    }
    cout << total << endl;
}
 
signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
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
