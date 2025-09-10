#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define print(msg, v) cerr << msg; for(auto x: v) cerr << x << " "; cerr << endl
#define all(v) v.begin(),v.end()

/*
Let dp[i] = number of good partitions on prefix [0..i]
(no string s has a leading 0, and l <= int(s) <= r)

set dp2[i] = dp[i] if i+1 is not 0, else 0
(since using dp[i] at i means a leading 0 on next partition ==> can't use (0 options)
*/

const i64 MOD = (i64)998244353;

vector<i64> zfunc(const string s){
	i64 l = 1, r = 0;
	const i64 n = s.size();
	vector<i64> z(n);
	z[0] = n;
	for (i64 i = 1; i < n; i++){
		// s[i-l]...s[r-l] = s[i]...s[r] (I)
		// but if z[i-l] = k then also
		// s[0]...s[k-1] = s[i-l]...s[i-l+k-1]
		// so if k <= r-i then because of the maximality of z[i-l], s[0..k-1] = s[i...i+k-1] and s[k] != (s[i-l+k] = s[i+k])
        // where the equality follows from (I) since i+k <= r
		// which means we can't expand prefix/prefix pair and z[i] = z[i-l]
		// Otherwise, if k > r-i, this means s[0...r-i] == s[i-l...r-l] == s[i...r]
        // so we reset the i64erval from [l,r] to [i,r] and try to expand it
		if (i > r){
			// outside i64erval, reset to empty closed i64erval
			l = i;
			r = i - 1;
		}
		if (z[i - l] <= r - i){
			z[i] = z[i - l];
		} else {
            l = i;
			while (r + 1 < n && s[r + 1] == s[r + 1 - i]){
				++r;
			}
			z[i] = r - i + 1;
		}
	}
	return z;
}


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, l, r;
    cin >> a >> l >> r;

    string lstr = l + a, rstr = r + a;
    auto zl = zfunc(l + a), zr = zfunc(r + a);

    // binary search for last (largest) idx j such that
    // a[j..i] >= l, i.e upper bound
    auto ub = [&a, &l, &zl](i64 i){
        i64 lo = 0, hi = i, ans = -1;
        const i64 n = l.size();
        while (lo <= hi){
            const i64 mid = lo + (hi - lo) / 2;
            // a[mid..i] >= l
            // iff zfunction on l+a
            // is >= |l|
            // OR it is not, but a[i + z[mid]] > l[z[mid]]
            if (i - mid + 1 < n) {  // not enough chars
                hi = mid - 1;
            } else if (i - mid + 1 > n){  // more than enough chars
                ans = mid;
                lo = mid + 1;
            } else {
                // just to ensure not overflowing
                const i64 z = min(zl[mid + n], n);
                if (z >= n || a[mid + z] > l[z]){
                    ans = mid;
                    lo = mid + 1;
                } else hi = mid - 1;
            }
        }
        return ans;
    };

    // binary search for first (smallest) idx j such that
    // a[j..i] <= r, i.e lower bound
    auto lb = [&a, &r, &zr](i64 i){
        i64 lo = 0, hi = i, ans = i + 1;
        while (lo <= hi){
            const i64 mid = lo + (hi - lo) / 2;
            const i64 m = r.size();
            if (i - mid + 1 > m){ // too many
                lo = mid + 1;
            } else if (i - mid + 1 < m){ // less char=smaller
                ans = mid;
                hi = mid - 1;
            } else {
                const i64 z = min(zr[m + mid], m);
                if (z >= m || a[mid + z] < r[z]){
                    ans = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
        }
        return ans;
    };

    const i64 n = a.size();
    vector<i64> dp(n + 1), dp2(n + 1), pref_dp(n + 1);

    dp[0] = 1;  // empty partition satisfies this by vacuity
    dp2[0] = a[0] != '0';
    pref_dp[0] = dp2[0];
    for (i64 i = 0; i < n; i++){
        i64 L = lb(i), R = ub(i);
        // 1-index L,R 
        ++L; ++R;
        // cerr << "for i=" << i + 1 << " L=" << L << " R=" << R << endl;
        if (L > R){
            dp[i + 1] = 0;
            dp2[i + 1] = 0;
            pref_dp[i + 1] = pref_dp[i];
        } else {
            // range sum over [L-1..R-1] over dp2
            // SPECIAL CASE: if R=i + 1, then we can take dp[i] instead of dp2[i]
            // into account because a single 0 is fine
            if (R == i + 1){
                dp[i + 1] = (
                    dp[i]
                    + (i > 0 ? pref_dp[i - 1] : 0)
                    + MOD
                    - (L-1 > 0 ? pref_dp[L - 2] : 0)
                ) % MOD;
            } else {
                dp[i + 1] = (pref_dp[R - 1] + MOD - (L-1 > 0 ? pref_dp[L - 2] : 0)) % MOD;
            }
            dp2[i + 1] = ((i + 1 < n && a[i + 1] == '0') ? 0 : dp[i + 1]);
            pref_dp[i + 1] = (dp2[i + 1] + pref_dp[i]) % MOD;
        }
    }
    cout << dp[n] << endl;
}
