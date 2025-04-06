#define testcases
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define endl '\n'
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define int long long
#define printmsg(msg, first, last) cerr << msg; for (auto it = first; it != last; it++) cerr << *it << " "; cerr << endl

void solve(){
    srand(time(NULL));
    i64 n;
    cin >> n;
    i64 a[3] = {1, 2, 3};
    i64 p = -1;
    bool first = true;

    vector<i64> v(n);
    iota(v.begin(), v.end(), (i64)0);

    std::random_device rd;
    std::mt19937 gen(rd());
    shuffle(v.begin(), v.end(), gen);
    // if inside triangle i, j, k there are c points, including p
    // and if inside triangle i,j,p there are c_k points (and c_i, c_j analogous)
    // then c_i + c_j + c_k + 1 = c ==> min(c_i, c_j, c_k) <= (c - 1) / 3
    // each time we choose min points reduces by 1/3, and probability of that is 1/3
    // ==> on average 75/3 = 25 good choices, and 25 >> (log_3 MAX_N) so a random algo works
    a[0] = v[0] + 1;
    a[1] = v[1] + 1;
    a[2] = v[2] + 1;
    while (p != 0){
        if (!first){
            i64 idx = rand() % 3;
            a[idx] = p;
        }
        first = false;
        cout << "? " << a[0] << " " << a[1] << " " << a[2] << endl;
        cout.flush();
        cin >> p;
    }
    cout << "! " << a[0] << " " << a[1] << " " << a[2] << endl;
    cout.flush();
}

signed main(){
    fastio;
    int t = 1;
    #ifdef testcases
    cin >> t;
    #endif
    while (t--) solve();
}
