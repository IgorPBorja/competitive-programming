#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

// since we want to minimize computer use
// we can assume teams spent 0 time on unsolved problems

signed main(){
    // binary search on number of computers

    // early first always works:
    // if prioritizing q[i] for 1 minute makes you lose q[j], then
    // C * (t[j] - (t + 1)) < work[j], which means that (since t[i] < t[j])
    // if you delayed working on q[i] for any time before the deadline, it would still impact t[j]
    // and the max work would still be C * (t[j] - (t + 1)) so you'd miss it anyway
    // ==> basically EDF

    i64 n;
    cin >> n;
    i64 work[n], t[n];
    for (i64 i = 0; i < n; i++) cin >> work[i];
    for (i64 i = 0; i < n; i++){
        cin >> t[i];
    }

    vector<pair<i64, i64>> tasks;
    for (i64 i = 0; i < n; i++){
        if (t[i] != -1){
            tasks.emplace_back(t[i], work[i]);
        }
    }
    sort(tasks.begin(), tasks.end(), [](pair<i64, i64> t1, pair<i64, i64> t2){
        return (t1.first < t2.first) || (t1.first == t2.first && t1.second > t2.second);
    });

    auto check = [](const i64 C, vector<pair<i64, i64>> tasks){  // pass-by-value, can't modify orig
        // cout << "--------->SEARCHING FOR C=" << C << endl;
        const i64 k = tasks.size();
        i64 cur_t = 0;
        i64 j = 0;
        while (j < k){
            // cout << "time cur_t=" << cur_t << endl;
            // NOTE: compress work that is only in a single task
            i64 dt = (tasks[j].second / C);
            tasks[j].second %= C;
            cur_t += dt;
            if (cur_t > tasks[j].first || (cur_t == tasks[j].first && tasks[j].second > 0)){
                // blows deadline
                return false;
            }

            i64 transition_work_unit = C;
            // use the transition work unit (guaranteed one j step ==> algo is O(n))
            while (j < k && transition_work_unit > 0){
                i64 delta = min(tasks[j].second, transition_work_unit);
                tasks[j].second -= delta;
                transition_work_unit -= delta;
                // cout << "took " << delta << " of task " << j + 1 << " ending with " << tasks[j].second << endl;
                if (tasks[j].second == 0){
                    // cout << "finished task " << j + 1 << endl;
                    ++j;
                }
            }
            ++cur_t;
        }
        return true;
    };

    i64 l = 1, r = (i64)(1e9), ans = (i64)1e9; // 1e4 pcs on each of the 1e5 problems solves in a single unit
    while (l <= r){
        const i64 m = l + (r - l) / 2;
        if (check(m, tasks)){
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << ans << endl;
}