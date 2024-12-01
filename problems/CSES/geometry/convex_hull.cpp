// #define TESTCASES
#define INCLUDE_COLLINEAR true

#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
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

// counterclockwise convex hull, includes collinear points
vector<pt> convex_hull(vector<pt> poly){
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


void solve(){
    i64 n;
    cin >> n;
    vector<pt> poly;
    for (i64 i = 0; i < n; i++){
        i64 x, y;
        cin >> x >> y;
        poly.emplace_back(x, y);
    }
    vector<pt> h = convex_hull(poly);
    cout << h.size() << endl;
    for (const pt& p: h){
        cout << p.x << " " << p.y << endl;
    }
}

signed main(){
    i64 t = 1;
#ifdef TESTCASES
    cin >> t;
#endif
    while(t--){
        solve();
    }
}