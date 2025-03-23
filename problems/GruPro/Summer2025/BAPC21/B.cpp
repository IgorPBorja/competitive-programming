#include <bits/stdc++.h>
using namespace std;

#define i64 int64_t

struct attr {
    string name;
    i64 target;
    i64 uses;
    i64 maximal_uses;
    bool is_first_extra;

    attr(string name, i64 target, i64 uses, i64 maximal_uses, bool is_first_extra) :
        name(name), target(target), uses(uses), maximal_uses(maximal_uses), is_first_extra(is_first_extra) {}
};

// in first extra point we win maximal_uses * target (late unlock) + uses
struct attr_less_than_comparator {
    bool operator()( const attr& lhs, const attr& rhs ) const {
        i64 lhs_delta, rhs_delta;
        if (lhs.is_first_extra){
            // is first extra point
            lhs_delta = lhs.target * lhs.maximal_uses + lhs.uses;
        } else {
            lhs_delta = lhs.uses;
        }
        if (rhs.is_first_extra){
            // is first extra point
            rhs_delta = rhs.target * rhs.maximal_uses + rhs.uses;
        } else {
            rhs_delta = rhs.uses;
        }
        if (lhs_delta < rhs_delta || (lhs_delta == rhs_delta && lhs.is_first_extra && !rhs.is_first_extra)){
            // prefer where is not first extra point
            return true;
        } else {
            return false;
        }
    }
};

signed main(){
    map<string, i64> baselines, target, cnt;
    i64 n, pts;
    cin >> n >> pts;
    for (i64 i = 0; i < n; i++){
        string s; i64 x;
        cin >> s >> x;
        baselines[s] = x;
        target[s] = 0;
    }
    i64 e;
    cin >> e;
    vector<pair<string, i64>> events(e);
    for (i64 i = 0; i < e; i++){
        cin >> events[i].first >> events[i].second;
        target[events[i].first] = max(target[events[i].first], events[i].second);
        ++cnt[events[i].first];
    }

    i64 min_delta = 0;
    for (auto[k, t]: target){
        min_delta += max(t - baselines[k], (i64)0);
    }
    if (min_delta > pts){
        cout << 0 << endl;
        return 0;
    }

    // forced point distribution for ties
    pts -= min_delta;

    i64 score = 0;
    map<string, i64> max_cnt;
    // find base score --> count of thresholds that are suboptimal for that key * target value
    for (auto[k, t]: events){
        if (t < max(target[k], baselines[k])){
            score += max(target[k], baselines[k]);
        } else {
            ++max_cnt[k];
        }
    }

    priority_queue<attr, vector<attr>,  attr_less_than_comparator> pq;
    for (auto[k, v]: target){
        pq.emplace(k, v, cnt[k], max_cnt[k], (v >= baselines[k]));
    }

    while (!pq.empty() && pts > 0){
        auto a = pq.top();
        pq.pop();
        if (a.is_first_extra){
            // put only one
            // so we win score (target + 1) * (uses where count is maximal)
            score += (a.target * a.maximal_uses) + a.uses;
            pq.emplace(a.name, a.target, a.uses, a.maximal_uses, false);
            --pts;
        } else {
            // use forever
            // win pts * uses
            score += pts * a.uses;
            pts = 0;
        }
    }
    cout << score << endl;
}