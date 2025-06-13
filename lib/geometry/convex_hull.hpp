#include "./point.hpp"
#include "./polygon.hpp"
#define i64 int64_t

// counterclockwise convex hull, can include collinear points or not
vector<pt> convex_hull(vector<pt> poly, bool INCLUDE_COLLINEAR){
    // choose bottommost point as pivot
    pt pivot = poly[0];
    const i64 n = poly.size();
    for (i64 i = 1; i < n; i++){
        if (poly[i].y < pivot.y || (poly[i].y == pivot.y && poly[i].x < pivot.x)){
            pivot = poly[i];
        }
    }
    sort(poly.begin(), poly.end(),
        [&pivot](pt p, pt q){return polarComp(pivot, p, q);}
    ); // pivot will be always poly[0] after sort
    // since including collinear points, we want to privilege the farthest collinear points
    // when coming back (e.g (0,0), (1,0), (2,0), (2,1), (2,2), (1,1))
    if (INCLUDE_COLLINEAR){
        i64 i = n - 1;
        while (i > 0 && orientation(pivot, poly[i], poly.back()) == 0){
            i--;
        }
        reverse(poly.begin() + i + 1, poly.end());
    }
    vector<pt> hull = {pivot};
    for (i64 i = 1; i < n; i++){
        while (
            hull.size() >= 2
            && (
                orientation(hull[hull.size() - 2], hull[hull.size() - 1], poly[i]) == 1
                || (!INCLUDE_COLLINEAR && orientation(hull[hull.size() - 2], hull[hull.size() - 1], poly[i]) == 0)
            )
        ){
            // goes clockwise, break orientation
            hull.pop_back();
        }
        hull.emplace_back(poly[i]);
    }
    return hull;
}
