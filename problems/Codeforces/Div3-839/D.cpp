#define TESTCASES

#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vb vector<bool>
#define vc vector<char>
#define vvi vector<vector<int>>
#define vvb vector<vector<bool>>
#define vvc vector<vector<char>>
#define vvpi vector<vector<pair<int, int>>>
#define pii pair<int, int>
#define eb emplace_back
#define ep emplace
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'

#define i32 int32_t
#define i64 int64_t
#define i128 int128_t

template <typename ForwardIterator>
void print(ForwardIterator itr, int n, string sep=" ")
{
    for (int i = 0; i < n; i++)
    {
        cout << *itr << sep;
        ++itr;
    }
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> v){
    for (T x: v){
        cout << x << " ";
    }
    return os;
}

template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> v){
    cout << "(" << v.first << ", " << v.second << ")";
    return os;
}

// struct Interval{
//     i64 min;
//     i64 max;
//     bool lopen;
//     bool ropen;

//     Interval(i64 min, i64 max, i64 lopen, i64 ropen){
//         this->min = min;
//         this->max = max;
//         this->lopen = lopen;
//         this->ropen = ropen;
//     }
// };

// Interval inter(Interval u1, Interval u2){
//     // logic for disjoint interval
//     // case 1: interval 1 to left
//     if (u1.max < u2.min || (u1.max == u2.min && (u1.ropen || u2.lopen))){
//         return Interval(1e18, 1e18, true, true);
//     } else if (u2.max < u1.min || (u2.max == u1.min) && (u2.ropen || u1.lopen)){
//         return Interval(1e18, 1e18, true, true);
//     }

//     // logic for overlapping interval
//     bool new_lopen, new_ropen;
//     if (u1.min > u2.min){
//         new_lopen = u1.lopen;
//     } else if (u2.min > u1.min){
//         new_lopen = u2.lopen;
//     } else {
//         new_lopen = u1.lopen || u2.lopen;
//     }
//     if (u1.max < u2.max){
//         new_ropen = u1.ropen;
//     } else if (u2.max < u1.max){
//         new_ropen = u2.ropen;
//     } else {
//         new_ropen = u1.ropen || u2.ropen;
//     }
//     return Interval(
//         max(u1.min, u2.min),
//         min(u1.max, u2.max),
//         // the openness of the intersection is there openness of the new endpoint
//         new_lopen,
//         new_ropen
//     )
// };

struct Interval{
    // closed intervals only
    i64 min;
    i64 max;

    Interval(i64 min, i64 max){
        this->min = min;
        this->max = max;
    }
};

Interval inter(Interval u1, Interval u2){
    // logic for disjoint interval
    // case 1: interval 1 to left
    if (u1.max < u2.min){
        return Interval(0, -1);
    } else if (u2.max < u1.min){
        return Interval(0, -1);
    } else if ((u1.min > u1.max) || (u2.min > u2.max)){
        // invalid interval
        return Interval(0, -1);
    }

    // logic for overlapping interval
    return Interval(
        max(u1.min, u2.min),
        min(u1.max, u2.max)
    );
}

void solve(){
    i64 n;
    cin >> n;
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    Interval curr = Interval(0, 1e9);
    for (i64 i = 0; i + 1 < n; i++){
        // check |a[i] - x| <= |a[i + 1] - x|
        // ==> closer to a[i]
        if (a[i] < a[i + 1]){
            // interval up to midpoint (floor, not ceil, to round down)
            curr = inter(curr, Interval(0, (a[i] + a[i + 1]) / 2));
        } else if (a[i] > a[i + 1]) {
            // interval above midpoint (ceil, not floor)
            curr = inter(curr, Interval((a[i] + a[i + 1] + 1) / 2, 1e9));
        }  // else equal, do nothing
    }

    if (curr.min <= curr.max){
        cout << curr.min << endl;
    } else {
        cout << -1 << endl;
    }
}

int main(){
#ifdef TESTCASES
    int t;
    cin >> t;
    while (t--){
        solve();
    }
#else
    solve()
#endif
    fastio;
}
