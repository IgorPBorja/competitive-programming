#include <bits/stdc++.h>
using namespace std;
#define i64 int64_t
#define all(v) v.begin(),v.end()
#define print(msg, v) cerr << msg; for (auto x: v) cerr << x << " "; cerr << endl

/*
A[i] = #(count of j such that h_j = i)
SOS(A)[i] = sum(s submask of i)A[s] = #(count of j such that h_j is a submask of i)

B[i] = choose(SOS(A)[i], 3) = #(amount of distinct triples h_j,h_k,h_l which are all submasks of i)
= #(amount of distinct triples h_j,h_k,h_l such that h_j | h_k | h_l is a submask of i)
= sum(s submask of i)#(amount of distinct triples h_j,h_k,h_l such that h_j | h_k | h_l = s)
= sum(s submask of i)X[s]

where X[s] is the answer for mask s. Therefore we want X = SOS^{-1}(B)

From sum(s submask of i)X[s] = B[i] we have:

B[0] = X[0]
B[2^i] = X[0] + X[2^i] ==> X[2^i] = B[2^i] - B[0]
B[2^i + 2^j] = X[0] + X[2^i] + X[2^j] + X[2^i + 2^j]
==> B[0] + B[2^i] - B[0] + B[2^j] - B[0] + X[2^i + 2^j] = B[2^i + 2^j]
==> X[2^i + 2^j] = B[2^i + 2^j] - B[2^i] - B[2^j] + B[0]

X[msk] = sum(s submask of msk)(-1)^{#(active bits of msk) - #(active bits of s)}B[s]

Thus if X[l][m] = sum(s submask of m, [s[N-1]..s[l] = m[N-1]..m[l]])(-1)^{#(active bits of msk) - #(active bits of s)}B[s] we have

* Se m[l - 1] = 0, s[l - 1] = 0 para toda submask s de m e logo X[l][m] = X[l - 1][m]
* Se m[l - 1] = 1, então temos dois casos:
	- Ou s[l - 1] = 1, com contribuição X[l - 1][m]
	- Ou s[l - 1] = 0, e portanto temos submasks de m XOR 2^(l-1), porém temos um bit ativo a mais
	em m em comparação a m XOR 2^(l-1), e portanto a contribuição é -X[l - 1][m ^ (1ll << (l - 1)]

o que é o mesmo que SOS DP, porém com os valores iniciais X[0][m] = (-1)^{#(active bits of m) - #(active bits of m)}B[m] = B[m]
 */

vector<i64> sosDP(const vector<i64>& a, i64 n){
	vector<i64> b = a;
	for (i64 i = 1; i <= n; i++){  // match msk[n-1]..msk[i]
		for (i64 msk = (1ll << n) - 1; msk >= 0; msk--){
			// b[msk] is equivalent to b[i - 1][msk] at the start of this iteration
			// (any b[j] is b[i - 1][j] for any j <= msk)
			if (msk & (1ll << (i - 1))){
				b[msk] += b[msk ^ (1ll << (i - 1))];
			}
		}
	}
	return b;
}

vector<i64> inv_sosDP(const vector<i64>& a, i64 n){
	vector<i64> b = a;
	for (i64 i = 1; i <= n; i++){
		for (i64 msk = (1ll << n) - 1; msk >= 0; msk--){
			if (msk & (1ll << (i - 1))){
				b[msk] -= b[msk ^ (1ll << (i - 1))];  // INVERTED SIGN
			}
		}
	}
	return b;
}

inline i64 choose3(i64 n){
	return (n * (n - 1) * (n - 2)) / 6;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	i64 n, k;
	cin >> n >> k;
	vector<i64> a(1ll << k, 0);
	for (i64 i = 0; i < n; i++){
		string h;
		cin >> h;
		reverse(all(h));
		i64 msk = 0;
		for (i64 j = 0; j < k; j++){
			if (h[j] == '1') msk |= (1ll << j);
		}
		++a[msk];
	}
	// print("a=", a);
	vector<i64> sa = sosDP(a, k);
	// print("sa=", sa);
	vector<i64> b(1ll << k);
	for (i64 msk = 0; msk < (1ll << k); msk++){
		b[msk] = choose3(sa[msk]);
	}
	vector<i64> ans = inv_sosDP(b, k);

	i64 m;
	cin >> m;
	for (i64 i = 0; i < m; i++){
		string h;
		cin >> h;
		reverse(all(h));
		i64 msk = 0;
		for (i64 j = 0; j < k; j++){
			if (h[j] == '1') msk |= (1ll << j);
		}
		cout << ans[msk] << endl;
	}
}
