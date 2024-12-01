// #define TESTCASES

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

i64 d2(pt p){
    return p.x * p.x + p.y * p.y;
}
pt operator+(pt p, pt q){
    return pt(p.x + q.x, p.y + q.y);
}
pt operator-(pt p, pt q){
    return pt(p.x - q.x, p.y - q.y);
}

// // strict-angle comparison (counter-clockwise!) with respect to pivot (0,0)
// bool operator<(pt p, pt q){
//     // edge cases (x=0 and y=0 lines) don't really matter
//     auto quadrant = [](pt p){
//         if (p.x >= 0 && p.y >= 0) return 0;
//         else if (p.x < 0 && p.y >= 0) return 1;
//         else if (p.x < 0 && p.y < 0) return 2;
//         else if (p.x >= 0 && p.y < 0) return 3;
//     };
//     if (quadrant(p) != quadrant(q)){
//         return quadrant(p) < quadrant(q);
//     }
//     i64 ccw = p.cross(q);
//     if (ccw > 0) return true;
//     else if (ccw < 0) return false;
//     // ccw = 0 => same line
//     // return the closest to the center
//     return d2(p) < d2(q);
// }

void solve(){
    i64 n;
    cin >> n;

    vector<pt> poly;
    for (i64 i = 0; i < n; i++){
        i64 x, y;
        cin >> x >> y;
        poly.emplace_back(x, y);
    }

    i64 area = 0;
    for (i64 i = 0; i < n; i++){
        area += (poly[(i + 1) % n].x - poly[i].x) * (poly[(i + 1) % n].y + poly[i].y);
    }
    cout << abs(area) << endl;
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