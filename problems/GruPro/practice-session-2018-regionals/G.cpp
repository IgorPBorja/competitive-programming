#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

const double PI = acos(-1);


signed main(){
    i64 n, total, d;
    double alpha, t;
    cin >> n >> total;
    cin >> alpha >> t >> d;


    // to radians
    alpha = (alpha * PI) / (double(180));
    i64 num_cycles = (i64)((double)total / t);
    const double base = ((alpha * num_cycles) / (double(2 * PI))) * t;
    const double rem = total - t * num_cycles;

    for (i64 i = 0; i < n; i++){
        i64 x, y;
        cin >> x >> y;
        double theta = atan2(double(y), double(x));
        if (x * x + y * y > d * d){
            cout << 0 << endl;
            continue;
        }
        double ans = base;
        if (theta <= alpha/2){
            ans += min(rem, ((theta + alpha/2) / (2 * PI)) * t);
            ans += rem - min(((2 * PI - alpha/2 + theta) / (2 * PI)) * t, rem);
        } else {
            // starts at theta-alpha/2 and ends at theta + alpha/2
            double start = (((theta - alpha/2)) / (2 * PI)) * t;
            double end = ((((theta + alpha/2))) / (2 * PI)) * t;
            ans += min(rem, end) - min(rem, start);
        }
        cout << fixed << setprecision(8) << ans << endl;
    }
}
