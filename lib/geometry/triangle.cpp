#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'

struct pt {
    i64 x, y;
    pt(i64 x, i64 y) : x(x), y(y) {}

    i64 cross(pt other){
        // [x other.x]
        // [y other.y]
        return x * other.y - y * other.x;
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

bool inside_triangle(pt q, pt p1, pt p2, pt p3){
    i64 oriented_area = 0;
    pt p[3] = {p1, p2, p3};
    for (i64 i = 0; i < 3; i++){
        oriented_area += (p[i] - q).cross(p[(i + 1) % 3] - q);
    }
    return oriented_area == 0;
}

// q is inside polygon p iff it belongs to some triangle
// p[0]p[i]p[i + 1], since those partition p
// Let i be the maximum 
bool inside_polygon(pt q, vector<pt> p){
    const i64 n = p.size();
}