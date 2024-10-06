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

vector<i64> poly_multiply(const vector<i64>& roots, const i64 l, const i64 r){
  if (l == r){
    return vector<i64>({1, -roots[l]});
  } else {
    const i64 m = l + (r - l) / 2;
    vector<i64> left = poly_multiply(roots, l, m), right = poly_multiply(roots, m + 1, r);
    vector<i64> ans(left.size() + right.size() - 1);
    for (u64 i = 0; i < left.size(); i++) {
      for (u64 j = 0; j < right.size(); j++) {
        ans[i + j] += left[i] * right[j];
      }
    }
    // calculate gcd to reduce the polynomial coef
    i64 gcd = abs(ans[0]);
    for (i64 i = 1; i < ans.size(); i++){
      gcd = __gcd(gcd, abs(ans[i]));
    }
    for (i64& x: ans){
      x /= gcd;
    }
    return ans;
  }
}

void solve(){
  string s;
  cin >> s;

  // try using (x - a) factors (MONIC)
  vector<i64> roots;
  i64 sign = 1;
  for (u64 i = s.size(); i >= 1; i--){
    if (s[i - 1] == 'H' && sign == -1){
      roots.emplace_back(2 * i + 1);
      sign = -sign;
    } else if (s[i - 1] == 'A' && sign == 1){
      roots.emplace_back(2 * i + 1);
      sign = -sign;
    }
  }

  // now try using a -1 in front
  // (-1) * MONIC
  vector<i64> alt_roots;
  sign = -1;
  for (u64 i = s.size(); i >= 1; i--){
    if (s[i - 1] == 'H' && sign == -1){
      alt_roots.emplace_back(2 * i + 1);
      sign = -sign;
    } else if (s[i - 1] == 'A' && sign == 1){
      alt_roots.emplace_back(2 * i + 1);
      sign = -sign;
    }
  }

  if (roots.size() == 0){
    cout << 0 << endl;
    cout << 1 << endl;
  } else if (alt_roots.size() == 0) {
    cout << 0 << endl;
    cout << -1 << endl;
  } else {
    vector<i64> ans;
    i64 final_sign = 1;
    if (roots.size() <= alt_roots.size()){
      ans = poly_multiply(roots, 0, roots.size() - 1);
    } else {
      ans = poly_multiply(alt_roots, 0, alt_roots.size() - 1);
      final_sign = -1;
    }
    for (i64& x: ans){
      x = final_sign * x;
    }
    cout << ans.size() - 1 << endl;
    for (i64 x: ans){
      cout << x << " ";
    }
    cout << endl;
    // // assert ok
    // auto eval = [&ans](i64 i){
    //   i64 ipow = 1;
    //   i64 val = 0;
    //   for (i64 j = ans.size() - 1; j >= 0; j--){
    //     val += ans[j] * ipow;
    //     ipow *= i;
    //   }
    //   return val;
    // };
    // for (i64 i = 1; i <= s.size(); i++){
    //   if (s[i - 1] == 'H'){
    //     assert(eval(2 * i) > 0);
    //   } else {
    //     assert(eval(2 * i) < 0);
    //   }
    // }
  }
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
