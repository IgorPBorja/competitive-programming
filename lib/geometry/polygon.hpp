#include "./point.hpp" 
#include "./triangle.hpp"

// shoelace formula
double area(vector<pt>& p){
    i64 a = 0;
    i64 n = p.size();
    for (i64 i = 0; i < n; i++){
        a += p[i].cross(p[(i + 1) % n]);  // area of OP[i]P[i+1]
    }
    return (double)a / 2.0f;
}

// O(log n) check for boundary/inside convex polygon
// take the first pt (lexicographically) as reference (P0), and sort by polar order
// since polygon is convex, then P = U P[0]P[i]P[i+1] for i=1..n-2
// do binary search to find i, and then check for being inside triangle
// check for boundaries separately
const i64 INSIDE = 1;
const i64 BOUNDARY = 0;
const i64 OUTSIDE = -1;
i64 inside_polygon_convex(pt q, vector<pt> p){
    const i64 n = p.size();
    pt pivot = p[0];
    for (pt a: p){
        if (make_pair(a.x, a.y) < make_pair(pivot.x, pivot.y)){
            pivot = a;
        }
    }
    sort(p.begin(), p.end(), [&pivot](pt a, pt b){return polarComp(pivot, a, b);});

    i64 l = 1, r = n - 2, i = -1;
    while (l <= r){
        i64 m = l + (r - l) / 2;
        // is in P[0]P[m]P[m+1] iff P[m]P[0]Q is ccw but P[m+1]P[0]Q is cw
        if (ccw(p[m], p[0], q)){
            if (!ccw(p[m + 1], p[0], q)){
                i = m;
                break;
            } else {
                l = m + 1;
            }
        } else {
            r = m - 1;
        }
    }
    // inside_triangle includes boudaries
    if (i == -1 || !inside_triangle(q, p[0], p[i], p[i + 1])) return OUTSIDE;
    else if (
        on_segment(q, p[i], p[i + 1])
        || (i == 1 && on_segment(q, p[0], p[1]))
        || (i == n - 2 && on_segment(q, p[0], p[n - 1]))
    ){
        return BOUNDARY;
    } else return INSIDE;
}

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
