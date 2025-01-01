#define TESTCASES
#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
// no flush
#define endl '\n'

#define printmsg(msg, first, last) \
    cout << msg; \
    for (auto it = first; it != last; it++){ \
        cout << *it << " "; \
    } \
    cout << endl \

const i64 INF = 2e18;

i64 query(i64 a, i64 b){
    cout << "? " << a + 1 << " " << b + 1 << endl;
    cout.flush();
    i64 ans;
    cin >> ans;
    if (ans == -1){
        exit(0);
    }
    return ans - 1;  // 0-indexing
}

// invariant: a is attached, b is not
void build_path(
    i64 a,
    i64 b,
    bool attached[],
    i64 n,
    vector<pair<i64, i64>>& edges 
){
    i64 c = query(a, b), d = query(b, a);
    if (c == a && d == b){
        // edge
        attached[b] = true;
        edges.emplace_back(a, b);
        return;
    } else if (c == d){
        // odd number of nodes between them
        // NOTE: c might be attached, or not
        if (!attached[c]){
            build_path(a, c, attached, n, edges);
        }
        build_path(c, b, attached, n, edges);
    } else {
        // even and non-zero number of nodes between then
        // c is 1 unit closer to a then d
        if (!attached[c]){
            build_path(a, c, attached, n, edges);
        }
        if (!attached[d]){
            // since a->...->c->d we can't have an alternative path d->...->a
            // since graph is acyclic
            edges.emplace_back(c, d);
            attached[d] = true;
        }
        build_path(d, b, attached, n, edges);
    }
}

void solve(){
    i64 n;
    cin >> n;
    const i64 ROOT = 0;
    bool attached[n];
    fill(attached, attached + n, false);
    attached[ROOT] = true;
    vector<pair<i64, i64>> edges;
    for (i64 i = 1; i < n; i++){
        if (attached[i]) continue;
        build_path(
            ROOT, i, attached, n, edges
        );
    }
    cout << "! ";
    for (auto[u, v]: edges){
        cout << u + 1 << " " << v + 1 << " ";   
    }
    cout << endl;
    cout.flush();
}

signed main(){
    int t;
#ifdef TESTCASES
    cin >> t;
#endif
    while (t--){
        solve();
    }
}