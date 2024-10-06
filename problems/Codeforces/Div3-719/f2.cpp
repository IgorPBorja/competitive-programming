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


template<size_t N>
struct SegTree{
    vector<i64> seg;

    SegTree(){
        seg.resize(4 * N);
        seg.assign(4 * N, 0);
    }

    i64 query(
        i64 l, i64 r, 
        i64 node_l = 0, i64 node_r = N - 1, i64 node = 0
    ){
        i64 node_mid = node_l + (node_r - node_l) / 2;
        if (l == node_l && r == node_r){
            return this->seg[node];
        } else if (r <= node_mid){
            // all on left side
            return query(l, r, node_l, node_mid, 2 * node + 1);
        } else if (l > node_mid) {
            // all on right side
            return query(l, r, node_mid + 1, node_r, 2 * node + 2);
        } else {
            // mixed
            return query(l, node_mid, node_l, node_mid, 2 * node + 1)
            + query(node_mid + 1, r, node_mid + 1, node_r, 2 * node + 2);
        }
    }

    void update(
        i64 p, i64 x,
        i64 node_l = 0, i64 node_r = N - 1, i64 node = 0
    ){
        i64 node_mid = node_l + (node_r - node_l) / 2;
        if (p == node_l && p == node_r){
            this->seg[node] = x;
            return; // this returns avoids the later update
            // which would mess up the result
        } else if (p <= node_mid){
            // on left half
            update(p, x, node_l, node_mid, 2 * node + 1);
        } else if (p > node_mid){
            // on right half
            update(p, x, node_mid + 1, node_r, 2 * node + 2);
        }
        this->seg[node] = this->seg[2 * node + 1] + this->seg[2 * node + 2];
    }
};

void solve(){
    i64 n, t, k;
    cin >> n >> t;

    // keep a seg tree for the added 1 values
    // then already answered queries do not need to be asked again
    // keeping it to n queries max.
    SegTree<(i64)2e5> seg;
    vector<i64> prefix_orig(n + 1, -1);
    prefix_orig[0] = 0;
    for (i64 i = 0; i < t; i++){    
        cin >> k;
        i64 l = 0, r = n - 1;
        i64 mid, ans;
        while (l <= r){
            i64 tsum;
            mid = l + (r - l) / 2;
            if (prefix_orig[mid + 1] != -1){
                // has this info already
                tsum = prefix_orig[mid + 1] + seg.query(0, mid);
            } else {
                // has to query
                cout << "?" << " " << 1 << " " << mid + 1 << endl;
                cout.flush();
                cin >> tsum;
                prefix_orig[mid + 1] = tsum - seg.query(0, mid);
            }
            // target is the min pos such that pos + 1 - sum[0..pos] =  k
            // if pos + 1 - sum[0..pos] < k, go higher
            // else go lower
            // we get sum[0..pos] with 
            if (mid + 1 - tsum == k){
                // greedy reduce
                ans = mid;
                r = mid - 1;
            } else if (mid + 1 - tsum < k){
                l = mid + 1; // add more zeros
            } else {
                // remove zeros
                r = mid - 1;
            }
        }
        cout << "!" << " " << ans + 1 << endl;
        cout.flush();
        if (i + 1 < t){
            // flip bit in this position
            seg.update(ans, 1);
        }
    }
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
