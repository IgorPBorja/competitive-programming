#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

struct pt {
    i64 x, y;
 
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

// counterclockwise polar sort
bool polarComp(pt pivot, pt p, pt q){
    auto d2 = [](pt a){
        return a.x * a.x + a.y * a.y;
    };
    i64 o = orientation(pivot, p, q);
    if (o == -1) return true;
    else if (o == 1) return false;
    else {
        // collinear => return closest point
        return d2(p - pivot) < d2(q - pivot);
    }
}

// line intersection
bool line_line_intersect(pt a, pt b, pt c, pt d){
    return (
        (b - a).cross(d - c) != 0
        || (b - a).cross(c - a) == 0
    ); // not parallel, or equal lines (ab||cd and abc collinear)
}

// line ab, segment cd
bool line_segment_intersect(pt a, pt b, pt c, pt d){
    // c and d are in different half-planes
    // ==> different orientations
    // OR any triple abc, abd is collinear
    return orientation(c, a, b) * orientation(d, a, b) != 1;
}

// https://cp-algorithms.com/geometry/check-segments-intersection.html
bool segment_segment_intersect(pt a, pt b, pt c, pt d){
    auto inter1d = [](i64 l1, i64 r1, i64 l2, i64 r2){
        if (l1 < r1) swap(l1, r1);
        if (l2 < r2) swap(l2, r2);
        return max(l1, l2) <= min(r1, r2);
    };
    if (orientation(a, b, c) == 0 && orientation(a, b, d) == 0){
        // all four are collinear
        // reduces to 1d interval intersection
        return inter1d(a.x, b.x, c.x, d.x) && inter1d(a.y, b.y, c.y, d.y);
    }
    return 
        // different half-planes: line ab intersects segment cd
        (orientation(a, b, c) != orientation(a, b, d))
        // different half-planes: line cd intersects segment cd
        && (orientation(c, d, a) != orientation(c, d, b))
    ;
}

// horizontal ray from a, direction +-1, intersects segment cd?
// DOES include intersection at endpoints (cd) by default,
// verified by CSES "Point in Polygon"
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
