#include <bits/stdc++.h>
using namespace std;
 
// edges: (a, b, c) = directed edge from a to b with weight c
vector<int> negative_cycle(const vector<tuple<int, int, int>> edges, int n){
    // virtual vertex connects to all others with weight 0
    // so ALL negative cycles are reachable!
    // for that effect we just need to set d[u] = 0 for all u
    // (we don't need an actual new vertex)
    vector<int> d(n, 0);
    vector<int> source_list;
    vector<int> prev(n, -1);
    // all paths of size s
    for (int s = 0; s <= n; s++){
        bool any = false;
        for (auto[a, b, c]: edges){
            if (d[a] + c < d[b]){
                any = true;
                prev[b] = a;
                d[b] = d[a] + c;
            }
        }
        if (!any) break;
    }
 
    // run a (single) new iteration of relaxation
    int target = -1;
    for (auto[a, b, c]: edges){
        if (d[a] + c < d[b]){
            target = b;
            break;
        }
    }
    if (target != -1){
        vector<int> cyc;
        // might be a cycle end or a vertex reachable from a negative cycle
        int curr = target;
        vector<bool> vis(n);
        while (!vis[curr]) {
            cyc.emplace_back(curr);
            vis[curr] = true;
            // we might have prev[curr] == curr
            // (in case of self negative edges!)
            curr = prev[curr];
        }
        // now curr is a visited vertex (closed the cycle!)
        cyc.emplace_back(curr);
        reverse(cyc.begin(), cyc.end());
        while (cyc.back() != cyc[0]){
            cyc.pop_back(); // remove vertices reachable from the cycle but not in it
        }
        return cyc;
    } else {
		return vector<int>();
	}
}