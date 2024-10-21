#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t
#define printmsg(msg, first, last) cout << msg;for(auto it = first; it != last; it++){cout << *it << " ";} cout << endl
#define printchain(msg, c) cout << msg; for(int64_t x: c.chain){cout << x << " ";} cout << endl;

const i64 MAXN = 60;
const i64 MAXV = (i64)1e7 + 10;
const i64 INF = (i64)2e18 + 10;

vector<i64> generate_primes(){
    vector<i64> primes;
    array<bool, MAXV + 1> is_composite;
    is_composite.fill(false);
    for (i64 i = 2; primes.size() < MAXN; i++){
        if (is_composite[i]) continue;
        primes.emplace_back(i);
        for (i64 j = i * 2; j <= MAXV; j += i){
            is_composite[j] = true;
        }
    }
    return primes;
}

struct Chain {
    i64 parent_idx;
    vector<i64> chain;

    Chain(i64 parent_idx) : parent_idx(parent_idx) {}
};

// compares chain references (the use of references avoids O(N) copying and guarantees O(1) comparison)
bool comp(const Chain& c1, const Chain& c2, const vector<i64>& value){
    i64 p1 = (c1.parent_idx == -1) ? 1 : value[c1.parent_idx];
    i64 p2 = (c2.parent_idx == -1) ? 1 : value[c2.parent_idx];
    return (c1.chain.size() > c2.chain.size()) || (
        c1.chain.size() == c2.chain.size() && p1 > p2
    );
}

struct DivisorChain {
    vector<i64> value;
    vector<vector<i64>> tree;
    vector<i64> subtree_depth;
    vector<Chain> chains;
    i64 n;

    DivisorChain(vector<vector<i64>> tree) : tree(tree) {
        this->value.assign(tree.size(), 1);
        this->subtree_depth.resize(tree.size());
        this->n = tree.size();
        this->sort_by_max_depth();

        Chain init(-1);
        discover_chain(0, init);
        vector<i64> primes = generate_primes();
        auto chain_ptr_comp = [this](Chain* c1, Chain* c2){return comp(*c1, *c2, this->value);};

        sort(this->chains.begin(), this->chains.end(), [this](const Chain& c1, const Chain& c2){return comp(c1, c2, this->value);});
        i64 sz = chains[0].chain.size();
        i64 i = 0, p_idx = 0;
        for (; sz > 0 && i < n; sz--){
            vector<Chain*> new_chains;
            while (i < n && this->chains[i].chain.size() == sz){
                new_chains.emplace_back(&this->chains[i]);
                ++i;
            }
            if (new_chains.size() == 0) continue; // no chains that size

            sort(new_chains.begin(), new_chains.end(), chain_ptr_comp);
            for (i64 j = 0; j < new_chains.size(); j++){
                const Chain& c = *new_chains[j];  // avoid copying
                i64 prime_power = (c.parent_idx == -1) ? 1 : primes[p_idx];  // first chain starts with 1
                for (const i64 x: c.chain){
                    this->value[x] = prime_power;
                    if (c.parent_idx != -1) this->value[x] *= this->value[c.parent_idx];
                    prime_power *= primes[p_idx];
                }
                ++p_idx;

                sort(new_chains.begin() + j + 1, new_chains.end(), chain_ptr_comp);
            }
        }
    }

    i64 sort_by_max_depth(i64 u = 0){
        subtree_depth[u] = 0;
        for (i64 v: this->tree[u]){
            subtree_depth[u] = max(subtree_depth[u], sort_by_max_depth(v) + 1);
        }
        sort(this->tree[u].begin(), this->tree[u].end(), [this](i64 v, i64 w){
            return this->subtree_depth[v] < this->subtree_depth[w];
        });
        reverse(this->tree[u].begin(), this->tree[u].end());
        return subtree_depth[u];
    }

    void discover_chain(i64 u, Chain& chain){
        chain.chain.emplace_back(u);

        // leaf node
        if (this->tree[u].size() == 0){
            chains.emplace_back(chain);
            return;
        }

        discover_chain(tree[u][0], chain);

        // now attribute chain

        for (i64 i = 1; i < tree[u].size(); i++){
            Chain new_chain(u);
            discover_chain(tree[u][i], new_chain);
        }
    }
};

void make_dag(i64 u, const vector<vector<i64>>& undirected_tree, vector<vector<i64>>& dag, i64 parent = -1){
    for (i64 v: undirected_tree[u]){
        if (v == parent) continue;
        dag[u].emplace_back(v);
        make_dag(v, undirected_tree, dag, u);
    }
}

signed main(){
    i64 n;
    cin >> n;
    vector<vector<i64>> tree(n);
    for (i64 i  = 0; i < n - 1; i++){
        i64 u, v;
        cin >> u >> v;
        --u; --v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    vector<vector<i64>> dag(n);
    make_dag(0, tree, dag);
    DivisorChain dchain(dag);
    for (const i64 val: dchain.value){
        cout << val << " ";
    }
    cout << endl;
}