// #define TESTCASES
 
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

vector<vector<i64>> components;
vector<vector<i64>> adj;
vector<bool> vis;
vector<i64> p;
i64 n, a, b;

i64 bsearch(const vector<i64>& c, i64 x){
    i64 l = 0, r = c.size() - 1;
    // minor optimization
    if (x < c[0] || x > c[c.size() - 1]){
        return -1;
    }

    while (l <= r){
        i64 mid = l + (r - l);
        if (c[mid] == x){
            return mid;
        } else if (x > c[mid]){
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

// O(sum 2 * c_i log (c_i)) = O(n log n)
i64 matches(vector<i64>& c){
    sort(c.begin(), c.end());
    bool a_ok = true, b_ok = true;

    for (i64 x: c){
        a_ok &= (bsearch(c, a - x) != -1);
    }
    if (a_ok) return 0;

    for (i64 x: c){
        b_ok &= (bsearch(c, b - x) != -1);
    }
    if (b_ok) return 1;
    return -1;
}

// O(|V| + |E|) = O(n + 2n) = O(n)
void bfs(i64 u, i64 c){
    components.emplace_back(vector<i64>()); // new
    queue<i64> q;
    q.emplace(u);
    while (!q.empty()){
        i64 v = q.front();
        q.pop();
        if (vis[v]) continue;
        vis[v] = true;
        components[c].emplace_back(p[v]); // emplace value not idx
        for (i64 w: adj[v]){
            if (!vis[w]){
                q.emplace(w);
            }
        }
    }
}

void solve(){
    cin >> n >> a >> b;
    p.resize(n);
    vis.assign(n, false);
    adj.resize(n);
    vector<i64> const_p(n);

    for (i64 i = 0; i < n; i++){
        cin >> p[i];
        const_p[i] = p[i];
    }
    // O(n log n)
    sort(p.begin(), p.end()); // IMPORTANT

    // O(n log n)
    for (i64 i = 0; i < n; i++){
        i64 apos = bsearch(p, a - p[i]);
        i64 bpos = bsearch(p, b - p[i]);
        if (apos != -1){
            adj[i].emplace_back(apos);
        }
        if (b != a && (bpos != -1)){
            adj[i].emplace_back(bpos);
        }
    }

    // O(|V| + |E|) = O(n + n*O(1)) = O(n)
    i64 c = 0;
    for (i64 i = 0; i < n; i++){
        if (!vis[i]){
            bfs(i, c);
            ++c;
        }
    }

    // O(n log n)
    map<i64, i64> s;
    for (vector<i64> c: components){
        i64 ans = matches(c);
        if (ans == -1){
            cout << "NO" << endl;
            return;
        } else {
            for (i64 x: c){
                s[x] = ans;
            }
        }
    }

    cout << "YES" << endl;
    for (i64 x: const_p){
        cout << s[x] << " ";
    }
    cout << endl;
}
 
signed main(){
	fastio;
#ifdef MYDEBUG
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
