// #define TESTCASES
// #define DEBUG
 
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
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
 
#define print(vec) for(auto x: vec){cerr << x << "|";} cerr << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

// priority queue: try to place the current largest (in time needed) FIRST
// when a smallest one enters, it becomes a priority
void solve(){
    i64 n;
    cin >> n;
    
    vector<pair<i64, i64>> x(n);
    map<i64, i64> cnt;
    for (i64 i = 0; i < n; i++){
        cin >> x[i].first;
    }
    for (i64 i = 0; i < n; i++){
        cin >> x[i].second;
    }

    sort(x.begin(), x.end(), [](pair<i64, i64> p1, pair<i64, i64> p2){
        return (p1.first < p2.first) || (p1.first == p2.first && p1.second > p2.second);
    });
    i64 min_cost = 0;

    // sort x by position and then by largest element
    // set current ptr to x[i] and move the ptr while there are positions before
    i64 r = 0;
    i64 curr_weight = 0;
    multiset<i64> times;

    for (i64 i = 0; i < n; i++){
        if (x[i].first > r){
            // let it unload first
            while (times.size() > 0 && r < x[i].first){
                // place largest element in the current position (no cost)
                i64 t = -(*times.begin());
                curr_weight -= t;
                times.erase(times.begin());

                // apply +1 offset to everyone to move minimum to r + 1
                min_cost += curr_weight;
                ++r;
            }
            r = max(r, x[i].first);  // needed in case there was not enough to fill the gap
        }
        curr_weight += x[i].second;
        times.insert(-x[i].second);
    }

    while (times.size() > 0){
        // place largest element in the current position (no cost)
        i64 t = -(*times.begin());
        curr_weight -= t;
        times.erase(times.begin());

        // apply +1 offset to everyone to move minimum to r + 1
        min_cost += curr_weight;
    }

    cout << min_cost << endl;
}


signed main(){
	fastio;
#ifdef DEBUG
	freopen("/tmp/in", "r", stdin);
#endif
	int t;
#ifdef TESTCASES
	cin >> t;
#else
	t = 1;
#endif
	while (t--){
		solve();
	}
}

