#define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'

struct pt {
    i64 x, y;

    pt(i64 x, i64 y) : x(x), y(y) {}
    pt(const pt& p) : x(p.x), y(p.y) {}

    i64 cross(pt p){
        return x * p.y - y * p.x;
    }
    void operator=(const pt q){
        x = q.x;
        y = q.y;
    }
};

pt operator+(pt p, pt q){
    return pt(p.x + q.x, p.y + q.y);
}
pt operator-(pt p, pt q){
    return pt(p.x - q.x, p.y - q.y);
}
bool operator<(pt p, pt q){
    return (p.x < q.x || (p.x == q.x && p.y < q.y));
}

bool ccw(pt p, pt q, pt r){
    // qp to qr implies clockwise rotation
    return (p - q).cross(r - q) < 0;
}

bool interval_intersection(i64 a, i64 b, i64 c, i64 d){
    if (a > b) swap(a, b);
    if (c > d) swap(c, d);
    return max(a, c) <= min(b, d);
}

bool segment_intersection(pt p1, pt p2, pt p3, pt p4){
    pt p = p1, u = p2 - p1, q = p3, v = p4 - p3;

    // p + tu = q + sv
    // crossing by v: (p x v + t u x v) = q x v + s (v x v) = q x v
    // ==> t (u x v) =  (q - p) x v
    // by symmetry: s (v x u) = (p - q) x u ==> s (u x v) = (q - p) x u
    // we must have 

    if (u.cross(v) == 0){
        // u and v are collinear ==> parallel lines (u == k * v)
        // either both (q - p) x v = (q - p) x u = 0 or none are 0
        if ((q - p).cross(u) == 0){
            // segments are completely colinear, we just need x axis intersection
            // (or in case of vertical, y axis intersection)
            return (p1.x == p2.x)
                ? interval_intersection(p1.y, p2.y, p3.y, p4.y)
                : interval_intersection(p1.x, p2.x, p3.x, p4.x);
        } else {
            // segments are parallel but never intersecting
            return false;
        }
    } else {
        // different lines
        // assure 0 <= t <= 1 and 0 <= s <= 1
        if (u.cross(v) > 0){
            return (q - p).cross(v) >= 0 && (q - p).cross(u) >= 0
            && u.cross(v) >= max((q - p).cross(v), (q - p).cross(u));
        } else if (u.cross(v) < 0){
            return (q - p).cross(v) <= 0 && (q - p).cross(u) <= 0
            && u.cross(v) <= min((q - p).cross(v), (q - p).cross(u));
        }
        assert(false);
    }
}

void solve(){
    i64 x1, y1, x2, y2, x3, y3, x4, y4;
    cin >> x1 >> y1;
    cin >> x2 >> y2;
    cin >> x3 >> y3;
    cin >> x4 >> y4;
    pt p1(x1, y1), p2(x2, y2), p3(x3, y3), p4(x4, y4);

    cout << (segment_intersection(p1, p2, p3, p4) ? "YES" : "NO") << endl;
}

signed main(){
    i64 t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--) solve();
}