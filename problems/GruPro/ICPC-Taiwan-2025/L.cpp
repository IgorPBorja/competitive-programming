#define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define print(msg, v) debug << msg; for(auto it = v.begin(); it != v.end(); it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

struct pt {
    i64 x, y;

    pt(i64 _x, i64 _y) : x(_x), y(_y) {}
    pt(const pt& p) : x(p.x), y(p.y) {}
    i64 cross(pt p){
        return x * p.y - y * p.x;
    }
    i64 dot(pt p){
        return x * p.x + y * p.y;
    }
    void operator=(const pt q){
        x = q.x;
        y = q.y;
    }
};
pt operator-(pt p1, pt p2){
    return pt(p1.x - p2.x, p1.y - p2.y);
}
pt operator+(pt p1, pt p2){
    return pt(p1.x + p2.x, p1.y + p2.y);
}

i64 orientation(pt p, pt q, pt r){
    i64 o = (q - p).cross(r - p);
    if (o > 0) return -1;  // ccw
    else if (o < 0) return 1;  // cw
    else return 0;  // collinear
}

bool segment_segment_intersect(pt a, pt b, pt c, pt d){
    auto inter1d = [](i64 l1, i64 r1, i64 l2, i64 r2){
        if (l1 < r1) swap(l1, r1);
        if (l2 < r2) swap(l2, r2);
        return max(l1, l2) <= min(r1, r2);
    };
    if (orientation(a, b, c) == 0 && orientation(a, b, d) == 0) {
        return inter1d(a.x, b.x, c.x, d.x) && inter1d(a.y, b.y, c.y, d.y);
    }
    return 
        (orientation(a, b, c) != orientation(a, b, d))
        && (orientation(c, d, a) != orientation(c, d, b));
}

bool segment_inside_rect(pt bottom_left, pt top_right, pt p, pt q){
    return
    (bottom_left.x <= p.x && p.x <= top_right.x)
    && (bottom_left.y <= p.y && p.y <= top_right.y)
    && (bottom_left.x <= q.x && q.x <= top_right.x)
    && (bottom_left.y <= q.y && q.y <= top_right.y);
}

void solve(){
    i64 xl, yl, xr, yr;
    i64 x1, y1, x2, y2;
    cin >> xl >> yl >> xr >> yr;
    cin >> x1 >> y1 >> x2 >> y2;
    pt p(x1, y1), q(x2, y2);
    if (
        segment_segment_intersect(pt(xl, yl), pt(xr, yl), p, q)
        || segment_segment_intersect(pt(xr, yl), pt(xr, yr), p, q)
        || segment_segment_intersect(pt(xr, yr), pt(xl, yr), p, q)
        || segment_segment_intersect(pt(xl, yr), pt(xl, yl), p, q)
        || segment_inside_rect(pt(xl, yl), pt(xr, yr), p, q)
    ){
            cout << "STOP" << endl;
    } else cout << "OK" << endl;
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
