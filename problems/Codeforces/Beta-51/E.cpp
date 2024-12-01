// #define TESTCASES
 
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

struct pt {
    i64 x, y;
    pt(i64 x, i64 y) : x(x), y(y) {}

    i64 cross(pt p){
        return x * p.y - p.x * y;
    }
};

i64 cross(pt p, pt q){
    return p.cross(q);
}

pt operator+(pt p, pt q){
    return pt(p.x + q.x, p.y + q.y);
}
pt operator-(pt p, pt q){
    return pt(p.x - q.x, p.y - q.y);
}
bool operator<(pt p, pt q){
    return (p.x < q.x) || (p.x == q.x && p.y < q.y);
}
ostream& operator<<(ostream& os, pt p){
    os << "(" << p.x << "," << p.y << ")";
    return os;
}

bool inside_tri(const pt q, const pt p1, const pt p2, const pt p3){
    pt p[3] = {p1, p2, p3};
    i64 area = 0;
    for (i64 i = 0; i < 3; i++){
        // p[i]qp[i + 1]
        area += abs(cross(p[i] - q, p[(i + 1) % 3] - q));
    }
    i64 total_area = abs(cross(p1 - p2, p3 - p2));
    // cout << "signed area=" << signed_area << endl;
    // cout << "total area=" << total_area << endl;
    return area == total_area;
}

bool inside_poly(const pt q, vector<pt> poly){
    const i64 n = poly.size();
    i64 l = 0, r = n - 1, ans = 0;
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        // p[0]p[m] -> p[0]q is clockwise?
        if (cross(poly[m] - poly[0], q - poly[0]) <= 0){
            ans = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    // cout << "last for q=" << q << " is=" << ans + 1 << endl;
    return inside_tri(q, poly[0], poly[ans], poly[(ans + 1) % n]);
}

void solve(){
    i64 n;
    cin >> n;
    vector<pt> poly;
    for (i64 i = 0; i < n; i++){
        i64 x, y;
        cin >> x >> y;
        poly.emplace_back(pt(x, y));
    }

    // i64 i = 0;
    // for (i64 j = 1; j < n; j++){
    //     if (poly[j] < poly[i]){
    //         i = j;
    //     }
    // }
    // rotate(poly.begin(), poly.begin() + i, poly.end());

    i64 T;
    cin >> T;
    for (i64 t = 0; t < T; t++){
        i64 x, y;
        cin >> x >> y;
        pt q(x, y);
        i64 l = 0, r = 0;
        i64 bad = 0;
        if (!inside_poly(q, poly)){
            cout << 0 << endl;
            continue;
        }
        for (; l < n; l++){
            while ((r + 1) % n != l && cross(poly[(r + 1) % n] - poly[l], q - poly[l]) <= 0){
                r = (r + 1) % n;
            }
            // r is the last before crossing q
            // so we take all (l, i, j) for l + 1 <= i < j <= r
            i64 clock_diff = (r + n - l) % n;
            // cout << "l=" << l + 1 << " r=" << r + 1 << " clock_diff=" << clock_diff << endl;
            bad += (clock_diff * (clock_diff - 1)) / 2;
        }
        // p[i]p[j]p[k] (clockwise) is only counted once
        cout << (n * (n - 1) * (n - 2)) / 6 - bad << endl;
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

