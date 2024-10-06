// #define TESTCASES
// #define DEBUG
 
#include <algorithm>
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
 
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
#define print(first, last) for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;
 
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

using point = pair<i64, i64>;

// subtract center, multiply by rotation matrix
// [cos90 -sin90] = [0 -1]
// [sin90  cos90] = [1  0]
// then sum the center again
point rot90(point p, point center, i64 k){
	if (k == 0) {
		return p;
	} else {
		point q;
		q.first = center.first - (p.second - center.second);
		q.second = center.second + (p.first - center.first);
		return rot90(q, center, k - 1);
	}
}

// // finds if pq and qr are perpendicular
// bool is_perp(point p, point q, point r){
// 	point a1 = make_pair(p.first - q.first, p.second - q.second);
// 	point a2 = make_pair(r.first - q.first, r.second - q.second);
// 	return (a1.first * a2.first + a1.second * a2.second == 0);
// }

i64 dist2(point p, point q){
	return (p.first - q.first) * (p.first - q.first) + (p.second - q.second) * (p.second - q.second);
}

// bool is_square(point pts[4]){
// 	// picks 3 points
// 	// check if they form a isosceles right triangle
// 	// do vector addition to find the fourth
// 	i64 d[3];
// 	d[0] = dist2(pts[0], pts[1]), d[1] = dist2(pts[1], pts[2]), d[2] = dist2(pts[0], pts[2]);
// 	sort(d, d + 3);
// 	if ((d[0] != d[1]) || (d[2] != (i64)2 * d[1])){
// 		return false;
// 	}
//
// 	for (i64 i = 0; i < 3; i++){
// 		if (dist2(pts[i], pts[(i + 1) % 3]) != d[0] || dist2(pts[i], pts[(i + 2) % 3]) != d[0]){
// 			continue;
// 		}
// 		point q = make_pair(pts[i].first + (pts[(i + 1) % 3].first - pts[i].first) + (pts[(i + 2) % 3].first - pts[i].first), pts[i].second + (pts[(i + 1) % 3].second - pts[i].second) + (pts[(i + 2) % 3].second - pts[i].second));
// 		return q == pts[3];
// 	}
// 	return false;
// }

bool is_square(point p[4]){
	do {
		bool ok = true;
		i64 d[4];
		for (i64 i = 0; i < 4; i++){
			d[i] = dist2(p[i], p[(i + 1) % 4]);
		}
		for (i64 i = 0; i < 4; i++){
			ok = ok & (d[i] == d[(i + 1) % 4]) & (d[i] > 0);
		}

		for (i64 i = 0; i < 4; i++){
			ok = ok & (p[(i + 2) % 4] == rot90(p[i], p[(i + 1) % 4], 1));
		}
		if (ok) return true;
	} while (next_permutation(p, p + 4));
	return false;
}

const i64 INF = 1e18;

void solve(){
	i64 n;
	cin >> n;

	point p[n][4], center[n][4];
	for (i64 i = 0; i < 4 * n; i++){
		cin >> p[i / 4][i % 4].first >> p[i / 4][i % 4].second;
		cin >> center[i / 4][i % 4].first >> center[i / 4][i % 4].second;
	}

	for (i64 i = 0; i < n; i++){
		i64 min_s = INF;
		for (i64 mask = 0; mask < (1ll << 8); mask++){
			i64 rot[4] = {
				mask % 4,
				(mask >> 2) % 4,
				(mask >> 4) % 4,
				(mask >> 6) % 4
			};
			point ps[4] = {
				rot90(p[i][0], center[i][0], rot[0]),
				rot90(p[i][1], center[i][1], rot[1]),
				rot90(p[i][2], center[i][2], rot[2]),
				rot90(p[i][3], center[i][3], rot[3])
			};
			if (is_square(ps)){
				min_s = min(min_s, accumulate(rot, rot + 4, (i64)0));
				// cout << "rot1=" << rot1 << " rot2=" << rot2 << " rot3=" << rot3 << " rot4=" << rot4 << endl;
				// cout << "min=" << min_s << endl;
				// print(ps, ps + 4);
			}
		}
		if (min_s < INF){
			cout << min_s << endl;
		} else {
			cout << -1 << endl;
		}
	}
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
