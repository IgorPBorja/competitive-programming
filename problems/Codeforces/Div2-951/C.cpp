#define TESTCASES
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

struct frac {
	i64 a, b;	

	frac(i64 a, i64 b) {
		i64 d = __gcd(a, b);
		this->a = a / d;
		this->b = b / d;
	}
	frac(i64 a) : a(a), b(1) {}
};

i64 __lcm(i64 a, i64 b){
	return (a * b) / __gcd(a, b);
}

frac operator+(frac f1, frac f2){
	i64 d = __gcd(f1.b, f2.b);
	i64 n1 = f2.b / d, n2 = f1.b / d;
	return frac(f1.a * n1 + f2.a * n2, f1.b * (f2.b / d));
}

frac operator-(frac f1, frac f2){
	i64 d = __gcd(f1.b, f2.b);
	i64 n1 = f2.b / d, n2 = f1.b / d;
	return frac(f1.a * n1 - f2.a * n2, f1.b * (f2.b / d));
}

frac operator*(frac f1, frac f2){
	return frac(f1.a * f2.a, f1.b * f2.b);
}

frac operator/(frac f1, frac f2){
	return frac(f1.a * f2.b, f1.b * f2.a);
}

frac operator*(i64 k, frac f1){
	return frac(k * f1.a, f1.b);
}

frac operator/(frac f1, i64 k){
	return frac(f1.a, k * f1.b);
}

void solve(){
	i64 n;
	cin >> n;
	i64 k[n];
	for (i64 i = 0; i < n; i++){
		cin >> k[i];
	}

	frac f(0, 1);
	for (i64 i = 0; i < n; i++){
		f = f + frac(1, k[i]);
	}
	if (f.a >= f.b){
		cout << -1 << endl;
		return;
	}

	frac epsilon = (frac(1, 1) - f) / n;


	// get minimum s
	i64 s = 1;
	for (i64 i = 0; i < n; i++){
		s = __lcm(s, k[i]);
	}
	s = __lcm(s, epsilon.b);

	i64 a[n];
	for (i64 i = 0; i < n; i++){
		frac base = frac(1, k[i]) + epsilon;
		a[i] = (s / base.b) * base.a;
	}

	for (i64 i = 0; i < n; i++){
		cout << a[i] << " ";
	}
	cout << endl;

	i64 sum = accumulate(a, a + n, 0), min_k = 2e18;
	for (i64 i = 0; i < n; i++) min_k = min(min_k, k[i] * a[i]);
	assert(min_k > sum);
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
