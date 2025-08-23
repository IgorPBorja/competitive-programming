#define TESTCASES
#define debug cerr

#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define endl '\n'
 
#define i64 int64_t
#define u64 uint64_t
#define i128 __int128
#define all(x) begin(x),end(x)
#define printmsg(msg, first, last) debug << msg; for(auto it = first; it != last; it++){debug << *it << " ";} debug << endl;
#define printgraph(msg, G) debug << msg << endl; \
	for (u64 u = 0; u < G.size(); u++) { \
		debug << "G[" << u << "]="; \
		for (u64 v: G[u]) { \
			debug << v << " "; \
		} \
		debug << endl; \
	}
 
template <typename T, typename U>
ostream& operator<< (ostream& out, pair<T, U> x)
{
	out << x.first << " " << x.second;
	return out;
}
template <typename T>
ostream& operator<< (ostream& out, vector<T> v)
{
	for (const auto& x: v){
		out << x << " ";
	}
	return out;
}

template <typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;
template <typename T>
using max_pq = priority_queue<T>;

const i64 B = 18;
vector<i64> p10(B + 1); // until 17
// sum_p10[i] = sum of digits until 10^i - 1
vector<i64> sum_p10(B + 1);
vector<i64> qtd_p10(B + 1);

/*
where 0 <= B < 10^k:
s[a * 10^k + B] = 
    dsum(0a1...ak) + ... + dsum((a-1)a1...ak)
    + dsum(a0..0) + sum(dsum(x) for x=a0...01->aB)
    = 10^k * (a-1)a/2 + a * s[10^k-1] + a + B*a + s[B]

so we do dp over digits to get log complexity
*/

i64 dsum(i64 x){
    i64 last = 0, cur;
    for (i64 k = B; k >= 0; k--){
        if (p10[k] > x) continue;
        cur = last;
        i64 a = x / p10[k];
        i64 new_x = x - a * p10[k];
        i64 total_over_digit = p10[k] * (((a - 1)*a)/2) + a * sum_p10[k] + a + new_x * a;
        cur += total_over_digit;
        x = new_x;
        last = cur;
    }
    return cur;
}

/*
where b < 10^k:
q[a * 10^k + B] = 
    dcount(0a1...ak) + ... + dcount((a-1)a1...ak)
    + dcount(a0..0) + sum(dcount(x) for x=a0...01->aB)

    Note that a0..00 -> aB have k+1 digits

    = q[10^k-1] + (a-1)*10^k * (k+1) + (new_x + 1)*(k + 1)
*/
i64 dcount(i64 x){
    i64 k = 0;
    i64 x_copy = x;
    while (x_copy >= 10){
        x_copy /= 10;
        ++k;
    }
    // now k is last exponent
    i64 a = x_copy;  // since x <= 10
    i64 new_x = x - a * p10[k];
    i64 total = qtd_p10[k] + (a - 1) * p10[k] * (k + 1) + (new_x + 1) * (k + 1);
    return total;
}

vector<i64> digits(i64 m){
    vector<i64> b10;
    while (m > 0){
        b10.emplace_back(m % 10);
        m /= 10;
    }
    return b10;
}

void solve(){
    i64 k;
    cin >> k;

    i64 l = 1, r = (i64)1e15;
    while (l <= r){
        i64 m = l + (r - l) / 2;
        i64 total = dsum(m);
        i64 qtd = dcount(m);
        // get digit count of m+1
        i64 x = m + 1, next_segment_digits = 0;
        while (x > 0){
            x /= 10;
            ++next_segment_digits;
        }
        // just before m + 1, but broken into it
        if (qtd == k){
            cout << total << endl;
            return;
        } else if (qtd <= k && qtd + next_segment_digits > k){
            vector<i64> next_segment = digits(m + 1);
            reverse(all(next_segment));
            for (i64 i = 0; i < k - qtd; i++){
                total += next_segment[i];
            }
            cout << total << endl;
            return;
        } else if (qtd < k){
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
}
 
signed main(){
    p10[0] = 1;
    for (i64 i = 1; i <= B; i++){
        p10[i] = p10[i - 1] * 10;
    }
    /*
    s[10^k-1] = (0+1+...+9)*10^{k-1} + 10 * s[10^{k-1}-1]
    q[10^k-1] = q[10^{k-1}+1] + (10^k-10^{k-1}) * i
    since it is >= 10^{i-1} and < 10^i the last block
    */
    sum_p10[0] = 0;
    qtd_p10[0] = 0;
    for (i64 i = 1; i <= B; i++){
        sum_p10[i] = p10[i - 1] * ((9 * 10) / 2) + sum_p10[i - 1] * 10;
        qtd_p10[i] = qtd_p10[i - 1] + (p10[i] - p10[i - 1]) * i;
    }

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
