// max segment tree
// lazy update: -1 on range
// query: find min pos such that pos >= x
// (strategy: search left if max(Left) >= x, else search right)

#include <bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define endl '\n'

vi st;
vi lazy; // amount to decrement
vi a;
const int INF = 2e9;

int build(int t, int tl, int tr)
{
    if (tl == tr)
    {
        st[t] = tl;
    }
    else
    {
        int tmid = tl + (tr - tl) / 2;
        st[t] = max(build(2*t + 1, tl, tmid), build(2*t + 2, tmid + 1, tr));
    }
    return st[t];
}

void advance_level(int t)
{
    if (lazy[t] != 0)
    {
        st[t] -= lazy[t];
        if (2*t + 1 < lazy.size())
        {
            lazy[2*t + 1] += lazy[t];
        }
        if (2*t + 2 < lazy.size())
        {
            lazy[2*t + 2] += lazy[t];
        }
        lazy[t] = 0;
    }

}

int query(int l, int r, int t, int tl, int tr)
{
    advance_level(t);
    if (l == tl && r == tr)
    {
        return st[t];
    }
    else
    {
        int tmid = tl + (tr - tl) / 2;
        if (r <= tmid)
            return query(l, r, 2*t + 1, tl, tmid);
        else if (l >= tmid + 1)
            return query(l, r, 2*t + 2, tmid + 1, tr);
        else
            return query(l, tmid, 2*t + 1, tl, tmid) + query(tmid + 1, r, 2*t + 2, tmid + 1, tr);
    }
}

int query_lb(int x, int t, int tl, int tr)
{
    advance_level(t);
    if (tl == tr)
        return st[t] >= x ? tl : INF;
    else
    {
        int tmid = tl + (tr - tl) / 2;
        // avoid checking children before potential lazy update !!!
        advance_level(2*t + 1);
        advance_level(2*t + 2);
        // decide to branch left or right
        if (st[2*t + 1] >= x) 
            return query_lb(x, 2*t + 1, tl, tmid);
        else if (st[2*t + 2] >= x)
            return query_lb(x, 2*t + 2, tmid + 1, tr);
        else
            return INF;
    }
}

void update(int l, int r, int t, int tl, int tr)
{
    if (lazy[t] != 0)
    {
        advance_level(t);
    }
    if (l == tl && r == tr)
    {
        --st[t];
        if (2*t + 1 < st.size())
        {
            ++lazy[2*t + 1];
            ++lazy[2*t + 2];
        }
    }
    else
    {
        int tmid = tl + (tr - tl) / 2;
        if (r <= tmid)
            update(l, r, 2*t + 1, tl, tmid);
        else if (l >= tmid + 1)
            update(l, r, 2*t + 2, tmid + 1, tr);
        else
        {
            update(l, tmid, 2*t + 1, tl, tmid);
            update(tmid + 1, r, 2*t + 2, tmid + 1, tr);
        }
        st[t] = max(st[2*t + 1], st[2*t + 2]);
    }
}

int main()
{
    int n;
    cin >> n;
    st.resize(4*n);
    lazy.resize(4*n);
    lazy.assign(4*n, 0);
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    build(0, 0, n - 1);
    int p;
    for (int i = 0; i < n; i++)
    {
        cin >> p;
        --p; // FIXES 1-INDEXING
        int transformed_p = query_lb(p, 0, 0, n - 1);
        cout << a[transformed_p] << ' '; 
        update(transformed_p, n - 1, 0, 0, n - 1);
    }
}