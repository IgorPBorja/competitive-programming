#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define all(x) x.begin(),x.end()
#define print(msg, v) cerr << msg; for (auto x: v) cerr << x << " "; cerr << endl

#define i64 int64_t

template<typename T>
using min_pq = priority_queue<T, vector<T>, greater<T>>;

const i64 INF = 1e18;

// u-> (w, v)
vector<i64> dijkstra(const vector<vector<pair<i64, i64>>>& adj, i64 src = 0){
    const i64 n = adj.size();
    vector<i64> dist(n, INF);
    min_pq<pair<i64, i64>> pq;
    pq.emplace(0, src);
    while (!pq.empty()){
        auto[d, u] = pq.top();
        pq.pop();
        if (d >= dist[u]) continue;
        dist[u] = d;
        for (auto[w, v]: adj[u]){
            if (d + w < dist[v]) pq.emplace(d + w, v);
        }
    }
    return dist;
}

const i64 MOD = (i64)1e9 + 7;

i64 bexp(i64 a, i64 p){
    if (p == 0) return 1;
    else {
        i64 b = bexp(a, p / 2);
        if (p % 2 == 0) return (b * b) % MOD;
        else return (a * ((b * b) % MOD)) % MOD;
    }
}

i64 inv(i64 a) { return bexp(a, MOD - 2); }

signed main(){
    fastio;

    i64 n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<i64, i64>>> adj(n);
    for (i64 i = 0; i < m; i++){
        i64 u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u); 
    }
    vector<i64> dist = dijkstra(adj, 0);

    vector<i64> fat(n + 1), ifat(n + 1);
    fat[0] = 1;
    for (i64 i = 1; i <= n; i++) fat[i] = (fat[i - 1] * i) % MOD;
    ifat[n] = inv(fat[n]);
    for (i64 i = n - 1; i >= 0; i--) ifat[i] = (ifat[i + 1] * (i + 1)) % MOD;

    auto binom = [&fat, &ifat](i64 n, i64 k){
        if (k > n) return (i64)0;
        else {
            return (fat[n] * ((ifat[k] * ifat[n - k]) % MOD)) % MOD;
        }
    };
    set<i64> __s;
    for (i64 d: dist) __s.emplace(d);
    vector<i64> unique_distances;
    for (i64 d: __s) unique_distances.emplace_back(d);
    const i64 unq = unique_distances.size();

    vector<i64> freq(unq, 0), suf_freq(unq, 0);
    for (i64 i = 0; i < n; i++){
        i64 j = lower_bound(all(unique_distances), dist[i]) - unique_distances.begin();
        ++freq[j];
    }
    for (i64 i = unq - 2; i >= 0; i--){
        suf_freq[i] = suf_freq[i + 1] + freq[i + 1];  // cnt of all with dist > unique_distances[i]
    }

    i64 expect = 0;
    // first unique distance is 0, does not count
    for (i64 i = 1; i < unq; i++){
        i64 d = unique_distances[i];
        if (freq[i] + suf_freq[i] >= k){
            i64 prob = (binom(freq[i] + suf_freq[i], k) + (MOD - binom(suf_freq[i], k))) % MOD;
            expect = (expect + d * prob) % MOD;
        }
    }
    expect = (expect * inv(binom(n - 1, k))) % MOD;  // divide by total possibilities
    cout << expect << endl;
}