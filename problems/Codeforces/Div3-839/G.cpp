#define TESTCASES

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

#define i32 int32_t
#define i64 int64_t
#define i128 int128_t

template <typename ForwardIterator>
void print(ForwardIterator itr, int n, string sep=" ")
{
    for (int i = 0; i < n; i++)
    {
        cout << *itr << sep;
        ++itr;
    }
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> v){
    for (T x: v){
        cout << x << " ";
    }
    return os;
}

template<typename T, typename U>
ostream& operator<<(ostream& os, pair<T, U> v){
    cout << "(" << v.first << ", " << v.second << ")";
    return os;
}

void solve(){
    i64 n;
    i64 start, end;

    cin >> n;
    cin >> start >> end; 
    i64 a[n];
    for (i64 i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a, a + n);

	i64 t[n], b[n];
	i64 cur = start;
	i64 maxdiff = 0, diff = 0;
	for (i64 i = 0; i < n; i++){
		if (cur >= a[i]){
			++cur;
			++diff;
			++maxdiff;
		} else {
			--cur;
			--diff;
		}
	}

	if (diff <= 0){
		if (maxdiff < end - start){
			cout << -1 << endl;
			return;
		} else {
			cout << end - start << endl;
			return;
		}
	}
	for (i64 i = 0; i < n; i++){
		if (cur >= a[i]){
			t[i] = 0;
			b[i] = start;
		} else {
			// grabbing up to a[i - 1] only!
			// maxdiff is i
			// total diff is i - (n - i) == 2i - n
			// t[i] = ceil((a[i] - b[i - 1] - i) / (2i - n))
			t[i] = t[i - 1] + max(a[i] - b[i - 1] - i + (2 * i - n - 1), 0) / (2 * i - n);
			b[i] = b[i - 1] + (2 * i - n) * (t[i] - t[i - 1]);
		}
	}

	// find first t[i] that surpasses
	// then we know we should only grab up to i - 1
	i64 upbound = 0;
	for (i64 i = 0; i < n; i++){
		if (b[i] >= end){
			// we know i > 0 now
			upbound = i;
			break;
		}
	}

	// resulting diff after grabbing a[i - 1] as last will be i - (n - i) = 2i - n
	// maxdiff will be i
	i64 rem_cycles = (end - b[upbound - 1] - upbound + (2 * upbound - n - 1)) / (2 * upbound - n);
	i64 after_rem = b[upbound - 1] + (2 * upbound - n) * rem_cycles;
	cout << t[upbound - 1] * n + rem_cycles * n + (end - after_rem) << endl;
}

int main(){
#ifdef TESTCASES
    int t;
    cin >> t;
    while (t--){
        solve();
    }
#else
    solve();
#endif
    fastio;
}
