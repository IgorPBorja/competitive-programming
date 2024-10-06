#define TESTCASES
#define DEBUG
 
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

const i64 MAXN = 2e5;
const i64 MOD = (i64)1e9 + 7;
i64 lowbit[MAXN + 1];
i64 max_lowbit[MAXN + 1];

vector<vector<i64>> compose(vector<vector<i64>> &a, vector<vector<i64>> &b){
	// O(n log^2 n composition)
	const i64 n = a.size() - 1;
	vector<vector<i64>> c(n + 1);
	for (i64 i = 1; i <= n; i++){
		c[i].assign(max_lowbit[i] + lowbit[i], 0);
		for (i64 j = 0; j < lowbit[i]; j++){
			for (i64 k = 0; k < lowbit[i - j]; k++){  
				c[i][j + k] = (c[i][j + k] + a[i][j] * b[i - j][k]) % MOD;
			}
		}
	}
	return c;
}

i64 bexp(i64 a, i64 p){
	if (p == 0){
		return a;
	} else {
		i64 m = bexp(a, p / 2);
		i64 x = ((1 - (p % 2)) + (p % 2) * a);
		return (((m * m) % MOD) * x) % MOD;
	}
}

i64 invmod(i64 a){
	return bexp(a, MOD - 2);
}

void solve(){
	i64 n, k;
	cin >> n >> k;

	i64 a[n + 1], b[n + 1];
	for (i64 i = 1; i <= n; i++){
		cin >> b[i];  // target
	}

	vector<vector<i64>> powers[31];
	vector<vector<i64>> base(n + 1);
	powers[0].resize(n + 1);
	for (i64 i = 1; i <= n; i++){
		powers[0][i].assign(lowbit[i], 1);
		base[i].assign(lowbit[i], 0);
		base[i][0] = 1;
	}
	for (i64 i = 1; i <= 30; i++){
		powers[i] = compose(powers[i - 1], powers[i - 1]);
	}

	vector<vector<i64>> fk = base;
	i64 exp = 0;
	while (k >= 1){
		i64 b = k % 2;
		if (b){
			fk = compose(powers[exp], fk);
		}
		k >>= 1;
		++exp;
	}

	// TODO REMOVE
	for (i64 i = 0; i <= 2; i++){
		for (i64 j = 1; j <= n; j++){
			string msg = "powers[" + to_string(i) +"][" + to_string(j) + "]: ";
			printmsg(msg, powers[i][j].begin(), powers[i][j].end());
		}
	}
	for (i64 j = 1; j <= n; j++){
		string msg = "fk[" + to_string(k) +"][" + to_string(j) + "]: ";
		printmsg(msg, fk[j].begin(), fk[j].end());
	}

	for (i64 i = 1; i <= n; i++){
		i64 target = b[i];
		for (i64 j = 1; j < fk[i].size(); j++){
			i64 val = (fk[i][j] * a[i - j]) % MOD;
			target = (target + (MOD - val)) % MOD;
		}
		a[i] = (target * invmod(fk[i][0])) % MOD;
	}

	for (i64 i = 1; i <= n; i++){
		cout << a[i] << " ";
	}
	cout << endl;
}
 
signed main(){
	max_lowbit[0] = -2e18;
	for (i64 i = 1; i <= MAXN; i++){
		i64 e = 1, j = i;
		while ((j & 1) == 0){
			j >>= 1;
			e++;
		}
		lowbit[i] = e;
		max_lowbit[i] = max(max_lowbit[i - 1], lowbit[i]);
	}

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
