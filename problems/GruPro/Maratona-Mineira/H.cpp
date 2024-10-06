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

const i64 M = 1e6;

namespace FFT {
	i64 _bit_reverse(i64 x, i64 sz){
		i64 ans = 0;
		for (i64 i = 0; i < sz; i++){
			i64 b = (x >> i) & 1;
			ans |= b << (sz - 1 - i);
		}
		return ans;
	}

	using C = complex<double>;
	void fft(vector<C> &A, bool invert){
		i64 logn = 0;
		while ((1ll << logn) < A.size()){
			++logn;
		}
		i64 n = 1ll << (logn);
		
		// create bit reversal order
		for (i64 i = 0; i < n; i++){
			// all indices are < 2^logn
			if (i < _bit_reverse(i, logn)){
				swap(A[i], A[_bit_reverse(i, logn)]);
			}
		}

		for (i64 block_sz = 2; block_sz <= n; block_sz <<= 1){
			// all updates use same base root of unite cis(2pi / block_sz)
			C w_base = (invert) ? 
				polar(1.0, -(double)acos(-1) * 2.0 / (double)block_sz)
				: polar(1.0, +(double)acos(-1) * 2.0 / (double)block_sz)
			;
			for (i64 align = 0; align < n; align += block_sz){
				C w(1);
				for (i64 off = 0; off < block_sz / 2; off++){
					// butterfly transformation
					// simultaneous update
					// A_k = A_k + w^(some exp) * A_{k + sz/2}
					// A_{k + sz/2} = A_k - w^(some exp) * A_{k + sz/2}
					C l = A[align + off], wr = w * A[align + off + block_sz / 2];
					A[align + off] = l + wr;
					A[align + off + block_sz / 2] = l - wr;
					w *= w_base;
				}
			}
		}
		if (invert){
			for (auto& x: A){
				x /= (double)A.size();
			}	
		}

		// undo swap / reordering (done only to make updating the coefficients easier)
		// for (i64 i = 0; i < padded_n; i++){
		// 	if (i < _bit_reverse(i, logn)){
		// 		swap(A[i], A[_bit_reverse(i, logn)]);
		// 	}
		// }
	}
	
	// convolution without precision tricks (like the sqrt cut)
	vector<i64> conv(const vector<int> &a, const vector<int> &b){
		const i64 n = a.size(), m = b.size();
		i64 lg = 0;
		while ((1ll << lg) < n + m - 1){
			++lg;
		}
		i64 s = 1ll << lg;
		
		vector<C> A(s), B(s);
		for (i64 i = 0; i < n; i++){
			A[i] = {(double)a[i], 0.0};
		}
		for (i64 i = 0; i < m; i++){
			B[i] = {(double)b[i], 0.0};
		}

		fft(A, false);
		fft(B, false);
		for (uint64_t i = 0; i < A.size(); i++){
			A[i] *= B[i];
		}
		fft(A, true);

		vector<i64> c(s);
		for (i64 i = 0; i < s; i++){
			c[i] = (i64)llround(A[i].real());
		}
		return c;
	}

	// vector<i64> conv(vector<i64> a, vector<i64> b){
	// 	i64 m = max(*max_element(a.begin(), a.end()), *max_element(b.begin(), b.end()));
	// 	
	// 	i64 cut = 1;
	// 	while (cut * cut < m){
	// 		cut *= (i64)2;
	// 	}
	// 	
	// 	vector<i64> a1(a.size()), a2(a.size()), b1(b.size()), b2(b.size());
	// 	for (uint64_t i = 0; i < a.size(); i++){
	// 		a1[i] = a[i] % cut;
	// 		a2[i] = a[i] / cut;
	// 	}
	// 	for (uint64_t i = 0; i < b.size(); i++){
	// 		b1[i] = b[i] % cut;
	// 		b2[i] = b[i] / cut;
	// 	}
	//
	// 	// (A1(x) + A2(x) * C) * (B1(x) + B2(x) * C)
	// 	// = A1(x)B1(x) + (A1(x)B2(x) + A2(x)B1(x))C + A2(x)B2(x) * C^2
	// 	vector<i64> c;
	// 	vector<i64> c11 = _unsafe_conv(a1, b1),
	// 		c12 = _unsafe_conv(a1, b2), 
	// 		c21 = _unsafe_conv(a2, b1),
	// 		c22 = _unsafe_conv(a2, b2)
	// 	;
	// 	c.resize(c11.size());
	// 	for (uint64_t i = 0; i < c.size(); i++){
	// 		c[i] = c11[i] + cut * (c12[i] + c21[i]) + cut * cut * c22[i];
	// 	}
	// 	return c;
	// }
}

void solve(){
	// we want to count the number of quadruples (i, j, k, l)
	// with x[i] - x[j] = y[k] - y[l]
	// which means the sum over the count array cx and cy
	// of all quadruples (a, b, c, d) such that a - b = c - d
	// <==> a + MAXV - b = c + MAXV - d
	// So we make convolution of cx with its reverse and cy with its reverse and calculate the product
	
	// polynomials for x axis are cx[0] + cx[1] * x + ... + cx[M] * x^M and cx[M] + cx[M - 1] * x + ... + cx[0] * x^M
	// k-th coefficient is sum(i + j == k)cx[i] * cx[M - j]
	// = sum(i + M - j == k)cx[i] * cx[j] = sum(i - j == k - M)cx[i] * cx[j]
	// and therefore for each difference d we want the coefficient M + d

	i64 n, m, x, y;
	vector<int> cx(M + 1);
	vector<int> rev_cx(M + 1);
	vector<int> waiting;

	cin >> n >> m;
	for (i64 i = 0; i < n; i++){
		cin >> x;
		++cx[x];
		++rev_cx[M - x];
	}
	for (i64 i = 0; i < m; i++){
		cin >> y;
		waiting.emplace_back(y);
	}

	vector<i64> u = FFT::conv(cx, rev_cx);
	for (i64 i = 0; i <= M; i++){
		cx[i] = 0;
		rev_cx[i] = 0;
	}
	for (i64 y: waiting){
		++cx[y];
		++rev_cx[M - y];
	}

	vector<i64> v = FFT::conv(cx, rev_cx);
	// printmsg("cx=", cx.begin(), cx.end());
	// printmsg("rx=", rev_cx.begin(), rev_cx.end());
	// printmsg(" u=", u.begin(), u.end());
	// printmsg(" v=", v.begin(), v.end());
	// discount the pairings (x, x) (i.e the same line!)
	u[M] -= n;
	v[M] -= m;
	i64 ans = 0;
	for (i64 i = 0; i <= M; i++){
		ans += u[i + M] * v[i + M];
	}

	cout << ans << endl;
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
