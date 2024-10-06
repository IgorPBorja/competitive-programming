#define TESTCASES

#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define i64 int64_t
#define endl '\n'

#define ep emplace
#define eb emplace_back

/*
* If d <= sqrt(n), use precomputed answer (O(n) for each d)
* Else, compute directly
*
*/

struct Query{
	i64 s, d, k;
	i64 i;
	Query(i64 s, i64 d, i64 k, i64 i) : s(s), d(d), k(k), i(i) {};
};

bool operator<(Query q1, Query q2){
	if (q1.d < q2.d){
		return true;
	}
	else if (q1.d == q2.d){
		if ((q1.s % q1.d) < (q2.s % q1.d)){
			return true;
		} else if ((q1.s % q1.d) == (q2.s % q1.d)){
			return (q1.k < q2.k) || (q1.k == q2.k && q1.i < q2.i);
		}
	}
	return false;
}

i64 isqrt(i64 n){
	i64 i;
	for (i = 0; i * i <= n; i++){}
	return i - 1;
} 

vector<i64> do_pref(vector<i64>& v){
	const i64 n = v.size();
	vector<i64> u(n + 1);
	u[0] = (i64)0;
	for (i64 i = 0; i < n; i++) u[i + 1] = u[i] + v[i];
	return u;
}

i64 direct(vector<i64>& a, Query q){
	i64 t = 0;
	for (i64 i = 0; i < q.k; i++){
		t += (i + 1) * a[q.s + i * q.d];
	}
	return t;
}

void solve(){
	i64 n, num_queries;
	cin >> n >> num_queries;
	i64 sqrtn = isqrt(n);
	vector<i64> a(n);
	for (i64 i = 0; i < n; i++) cin >> a[i];
	

	vector<Query> queries;
	for (i64 i = 0; i < num_queries; i++){
		i64 s, d, k;
		cin >> s >> d >> k;
		--s; // IMPORTANT -> 0-index
		queries.eb(Query(s, d, k, i));
	}
	sort(queries.begin(), queries.end());

	i64 cur_d = 0, cur_s = 0;
	vector<i64> epref, w, final_ans(num_queries);
	for (Query q: queries){
		if (q.d > sqrtn){
			final_ans[q.i] = direct(a, q);
			continue;
		}
		if ((q.d != cur_d) || ((q.s % cur_d) != cur_s)){
			// precompute sums	
			epref.clear();
			w.clear();
			epref.resize((n - 1 - (q.s % q.d)) / q.d + 2);
			epref[0] = 0;
			for (i64 i = 0; (q.s % q.d) + i * q.d < n; i++){
				epref[i + 1] = epref[i] + a[(q.s % q.d) + i * q.d];
			}
			w = do_pref(epref);
			cur_d = q.d; cur_s = q.s % q.d;
		}

		i64 j = q.s / q.d; // additional offset
		// we want for given k, k * (epref[k + j] - epref[j]) - (epref[k + j - 1] - epref[j]) - (epref[k + j - 2] - epref[j]) - ... - (epref[j + 1] - epref[j]) - (epref[j] - epref[j])
		// = k * (epref[k + j] - epref[j]) - (w[k + j] - w[j]) - k * epref[j]
		// = k * epref[k + j] - (w[k + j] - w[j]) 
		final_ans[q.i] = q.k * epref[q.k + j] - (w[q.k + j] - w[j]);
	}
	
	for (i64 i = 0; i < num_queries; i++){
		cout << final_ans[i] << " ";
	}
	cout << endl;
}

signed main(){
	fastio;
	int t = 1;
#ifdef TESTCASES
	cin >> t;
#endif
	while (t--) solve();
}
