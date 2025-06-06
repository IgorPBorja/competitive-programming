#include <bits/stdc++.h>

using namespace std;
#define printmsg(msg, first, last) cerr << msg;for(auto it = first; it != last; it++)cerr << *it << " ";cerr << endl;
#define all(a) a.begin(), a.end()
#define endl "\n"
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define i64 int64_t

const i64 B = 30;  // ai < 2^B
const i64 MOD = 998244353;

inline i64 sum_range(i64 l, i64 r){
    // l + (l + 1) + ... + r
    // = l * (r - l + 1) + (0 + 1 + ... + (r - l))
    return (
		(l * (r - l + 1)) % MOD + 
		(((r - l) * (r - l + 1)) / 2) % MOD
	) % MOD;
}

i64 bexp(i64 x, i64 p){
	if (p == 0){
		return 1;
	} else {
		const i64 y = bexp(x, p >> 1);
		const i64 y2 = (y * y) % MOD;
		if (p % 2 == 0){
			return y2;
		} else{
			return (y2 * x) % MOD;
		}
	}
}

i64 interval_sizes_from_pivots(vector<i64> p, i64 n){
    const i64 k = p.size();
    i64 delta = 0;
    if (k == 0){
        return 0;
    } else if (k == 1){
        // sum(i=0..p[0], j=p[0]..n-1)(j - i + 1) - 1
		// ends up being ((n - p[0]) * (p[0] + 1) * (n + 1)) / 2
        return (((n - p[0]) * (p[0] + 1) * (n + 1)) / 2) % MOD;
    }
    
    // update endpoint
    p.emplace_back(n);
    
    i64 parity_suf[k + 1];
    parity_suf[k] = 0;
    parity_suf[k - 1] = (p[k] - p[k - 1]) % MOD;
    for (i64 j = k - 2; j >= 0; j--){
        parity_suf[j] = (p[j + 1] - p[j] + parity_suf[j + 2]) % MOD;
    }
    // left anchors are -1, p[0], p[1], ..., p[k - 1]
    // right anchors are p[0], p[1], ..., p[k - 1], n
    i64 anchor_idx = 0;
    for (i64 j = 0; j < n; j++){
        if (j > p[anchor_idx]) ++anchor_idx;
        if (anchor_idx >= k) break;
        // (p[l - 1], p[l]] maps to [p[l + 2j], p[l + 2j + 1]) for all j >= 0
        // so sum (p[l + 2j + 1] - p[l + 2j]) over j which means parity_suf[l]
        // where l = anchor_idx
        delta = (delta + (MOD - j) * parity_suf[anchor_idx]) % MOD;
    }
    
    p.insert(p.begin(), (i64)(-1));
    i64 parity_pref[k + 1];
	parity_pref[0] = 0;
    parity_pref[1] = p[1] + 1;  // since p[0] = -1 now
    for (i64 j = 2; j <= k; j++){
        parity_pref[j] = (p[j] - p[j - 1] + parity_pref[j - 2]) % MOD;
    }
    anchor_idx = 0;
    for (i64 j = 0; j < n; j++){
        // [p[l], p[l + 1]) maps to (p[l - 2j - 1], p[l - 2j]] for all j >= 0
        // so sum(p[l - 2j] - p[l - 2j - 1]) for j >= 0
        // which means
        // NOTE: we should have a p[0] = -1
        if (j >= p[anchor_idx + 1]){
            // since p.back() is = n, bounds check is not needed
            ++anchor_idx;
        }
        delta = (delta + (j + 1) * parity_pref[anchor_idx]) % MOD;
		// the j + 1 is because of the +1 in (r - l + 1) in the formula in the statement
    }
    return delta;
}

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    
    i64 ans = 0;
    for (i64 i = 0; i < B; i++){
        vector<i64> p;
        for (i64 j = 0; j < n; j++){
            if (a[j] & (1ll << i)){
                p.emplace_back(j);
            }
        }
		const i64 delta = interval_sizes_from_pivots(p, n);
		ans = (ans + bexp((i64)2, i) * delta) % MOD;
        
    }
    cout << ans << endl;
}


signed main(){
    fastio;
    solve();
}
