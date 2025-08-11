#include <bits/stdc++.h>
using namespace std;

// sorts and returns count of inversions. Modifies original array!
int inversions(vector<int>& a, int l, int r){
    if (l == r) return 0;
    const int m = l + (r - l) / 2;
    int total = inversions(a, l, m) + inversions(a, m + 1, r);
    vector<int> left, right;
    for (int i = l; i <= m; i++) left.emplace_back(a[i]);
    for (int i = m + 1; i <= r; i++) right.emplace_back(a[i]);

    int idx = l;
    int pl = 0, pr = 0;
    while (pl < left.size() || pr < right.size()){
        // we only count the inversion pairs from the perspective of the smaller
        // element on the right
        // 1 3 5 | 2 4
        // if right[pr] < left[pl] then it is smaller than [left[pl]..[left[|left|-1]]]
        // so contributes for left-pl cross-inversions
        if (pr == right.size())
            a[idx++] = left[pl++];
        else if (pl == left.size())
            a[idx++] = right[pr++];
        else {
            if (left[pl] < right[pr]) 
                a[idx++] = left[pl++];
            else {
                a[idx++] = right[pr++];
                total += left.size() - pl;
            }
        }
    }
    return total;
}
