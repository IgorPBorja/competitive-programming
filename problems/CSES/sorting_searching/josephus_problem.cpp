#include <bits/stdc++.h>
using namespace std;
#define fastio                        \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL)
#define i64 int64_t
#define printmsg(msg, first, last) cout << msg; for(auto it = first; it != last; it++){cout << *it << "|";} cout << endl;


template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> p){
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

// solves the problem in the correct order
// each call processes a "round"
// if n is odd, n = 2k + 1
// 2, 4, .., 2k
// we apply the map 2k+1->1, 1->2, ..., 2k-1->k+1
// so we need to undo with the map 1->2k+1, 2->1, ..., k+1->2k-1
// and now we have the subproblem on size k
// since now default distance is 2 but it still starts at 1

// if n is even, n = 2k
// 2, 4, .., 2k
// now starts at 1 again, so we apply the map 1->1, 3->2, ...
// so we need to undo with the map 1->1, 2->3, 3->5, ...

// since subproblem always reduces by half there is at most O(log n) calls
// T(n) =  n + T(n / 2)
vector<i64> solve(i64 n){
    if (n == 0){
        return {};
    } else if (n == 1){
        return {1};
    }
    vector<i64> ans;

    for (i64 i = 1; i <= n / 2; i++){
        // cout << "for n=" << n << " adding " << 2 * i << endl;
        ans.emplace_back(2 * i);
    }
    // printmsg("ans=", ans.begin(), ans.end());
    vector<i64> r = solve((n + 1) / 2);
    // last (n+1)/2 elements
    if (n % 2 == 1){
        for (i64 x: r){
            if (x == 1) ans.emplace_back(n);
            else ans.emplace_back(2 * x - 3);
        }
    } else {
        for (i64 x: r){
            ans.emplace_back(2 * x - 1);
        }
    }
    return ans;
}


int main()
{
    i64 n;
    cin >> n;
    vector<i64> ans = solve(n);
    for (i64 x: ans){
        cout << x << " ";
    }
    cout << endl;
}
