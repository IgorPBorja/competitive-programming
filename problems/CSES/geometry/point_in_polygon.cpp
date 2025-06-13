#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

struct pt {
    i64 x, y;
 
    pt() {}
    pt(i64 x, i64 y) : x(x), y(y) {}
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
pt operator*(pt p1, i64 k){
    return pt(k * p1.x, k * p1.y);
}
pt operator*(i64 k, pt p1){
    return pt(k * p1.x, k * p1.y);
}

i64 orientation(pt p, pt q, pt r){
    i64 o = (q - p).cross(r - p);
    if (o > 0){
        return -1; // counterclockwise
    } else if (o < 0){
        return 1; // clockwise
    } else {
        return 0; // collinear
    }
}

i64 ccw(pt p, pt q, pt r) { return orientation(p, q, r) < 0; }
 

bool is_collinear(pt p, pt q, pt r){
    return (q - p).cross(r - p) == 0;
}

// is p on segment q,r?
bool on_segment(pt p, pt q, pt r){
    // pqr is collinear
    // qp and pr have the same sign/orientation (as p in between q and r)
    return (
        is_collinear(p, q, r)
        && ((p - q).dot(r - p) >= 0)
    );
}

// horizontal ray from a, direction +-1, intersects segment cd?
// DOES include intersection at endpoints (cd) by default,
bool horizontal_ray_segment_intersect(pt a, pt c, pt d, i64 direction = 1){
    if (c.y <= a.y && a.y < d.y){  // different half-planes from ray, c below or at line, d above
        // now we need d in the same half-plane as the ray (considering line ac)
        // so the intersection happens on the ray and not on the other side
        if (direction == 1){
            return orientation(c, a, d) > 0;
        } else {
            return orientation(c, a, d) < 0;
        }
    } else if (d.y <= a.y && a.y < c.y){
        return horizontal_ray_segment_intersect(a, d, c, direction);
    }
    return false;
}

const i64 OUTSIDE = -1, BOUNDARY = 0, INSIDE = 1;
// Raycasting algorithm, works on all polygons, convex or not. Complexity: O(N)
// if the ray intersects a vertex, then it only counts if orientation changes
// (so it does not hit "tangentially", but cuts through)
i64 inside_polygon(pt q, vector<pt>& p){
    const i64 n = p.size();
    // draw horizontal ray
    i64 ray_intersections = 0;
    for (i64 i = 0; i < n; i++){
        // p[i]p[i+1] 
        if (on_segment(q, p[i], p[(i + 1) % n])){
            return BOUNDARY;
        }
        ray_intersections += horizontal_ray_segment_intersect(q, p[i], p[(i + 1) % n]);
    }
    // to be inside: odd exits
    if (ray_intersections % 2 == 1){
        return INSIDE;
    } else {
        return OUTSIDE;
    }
}

signed main(){
    i64 n, m;
    cin >> n >> m;
    vector<pt> p(n);

    for (i64 i = 0; i < n; i++){
        cin >> p[i].x >> p[i].y;
    }

    pt q;
    for (i64 i = 0; i < m; i++){
        cin >> q.x >> q.y;
        i64 status = inside_polygon(q, p);
        if (status == INSIDE){
            cout << "INSIDE" << endl;
        } else if (status == OUTSIDE) {
            cout << "OUTSIDE" << endl;
        } else if (status == BOUNDARY) {
            cout << "BOUNDARY" << endl; 
        }
    }
}
