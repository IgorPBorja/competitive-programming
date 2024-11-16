//#define TESTCASES
 
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
 
#define print(vec) for(auto x: vec){cout << x << "|";} cout << endl;
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}

template<typename T>
void down(map<T, i64>& m, T x){
    --m[x];
    if (m[x] == 0){
        m.erase(x);
    }
}

template<typename T>
void up(map<T, i64>& m, T x){
    ++m[x];
}

struct Slide{
    map<i64, i64> lower, upper;
    i64 lower_size, upper_size;

    Slide(){
        lower_size = 0;
        upper_size = 0;
    }

    i64 median(){
        return lower.rbegin()->first;
    }

    void update(){
        i64 total = lower_size + upper_size;
        while (lower_size > (total + 1) / 2){
            i64 max_lower = lower.rbegin()->first;
            down(lower, max_lower);
            up(upper, max_lower);
            --lower_size;
            ++upper_size;
        }
        while (upper_size > total / 2){
            i64 min_upper = upper.begin()->first;
            down(upper, min_upper);
            up(lower, min_upper);
            --upper_size;
            ++lower_size;
        }
    }

    void insert(i64 x){
        if (lower.size() == 0 || x <= this->median()){
            up(lower, x);
            ++lower_size;
        } else {
            up(upper, x);
            ++upper_size;
        }
        this->update();
    }

    void remove(i64 x){
        if (lower.find(x) != lower.end()){
            down(lower, x);
            --lower_size;
        } else {
            down(upper, x);
            --upper_size;
        }
        this->update();
    }

};

void solve(){
    i64 n, k;
    cin >> n >> k;
    vector<i64> a(n);
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }

    Slide s;
    for (i64 i = 0; i < k; i++){
        s.insert(a[i]);
    }
    cout << s.median() << " ";

    for (i64 i = k; i < n; i++){
        s.insert(a[i]);
        s.remove(a[i - k]);
        cout << s.median() << " ";
    }
    cout << endl;
}
 
signed main(){
	fastio;
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