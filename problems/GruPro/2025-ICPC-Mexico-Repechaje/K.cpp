#include <bits/stdc++.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)

#define i64 int64_t

signed main(){
    fastio;
    i64 served = 0, n, m, o;
    cin >> n >> m >> o;

    vector<i64> q(n);
    vector<vector<pair<i64, i64>>> dishes(m);  // pair (ingredient idx, qtd)
    vector<vector<i64>> orders(o);

    // each order might have M items with N ingredients each ==> O * M * N to simulate
    for (i64 i = 0; i < n; i++) cin >> q[i];
    for (i64 i = 0; i < m; i++){
        i64 m_i;
        cin >> m_i;
        dishes[i].reserve(m_i);
        for (i64 j = 0; j < m_i; j++){
            i64 ing_idx, ing_qtd;
            cin >> ing_idx >> ing_qtd;
            --ing_idx;
            dishes[i].emplace_back(ing_idx, ing_qtd);
        }
    }
    auto process_dish = [&dishes, &q](i64 dish_idx){
        for (auto[i, qtd]: dishes[dish_idx]){
            if (qtd > q[i]) return false;
            q[i] -= qtd;
        }
        return true;
    };
    // cerr << "read all dishes" << endl;
    for (i64 i = 0; i < o; i++){
        i64 o_i;
        cin >> o_i;
        for (i64 j = 0; j < o_i; j++){
            i64 dish_idx;
            cin >> dish_idx;
            --dish_idx;
            if (!process_dish(dish_idx)){
                cout << served << endl;
                return 0;
            }
        }
        ++served;
        // cerr << "order i=" << i+1 << " ok" << endl;
    }
    cout << served << endl;
}