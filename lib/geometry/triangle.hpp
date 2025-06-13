#include "./point.hpp"

// pqr oriented area
// can also be calculated by shoelace
double area(pt p, pt q, pt r){
    return (double)((q - p).cross(r - p)) / 2.0f;
}

bool inside_triangle(pt q, pt p1, pt p2, pt p3){
    i64 abs_area = 0;
    pt p[3] = {p1, p2, p3};
    for (i64 i = 0; i < 3; i++){
        abs_area += abs((p[i] - q).cross(p[(i + 1) % 3] - q));
    }
    i64 total = abs((p[1] - p[0]).cross(p[2] - p[0]));
    return abs_area == total;
}
