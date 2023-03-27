#include <bits/stdc++.h>
using namespace std;

vector<int> st;

// O(log n)
void update(int p, int tl, int tr, int node, int delta)
{
    if (tl == tr && tr == p)
    {
        st[node] += delta;
    }
    else if (tl <= p && p <= tr)
    {
        int tmid = tl + (tr - tl) / 2;
        update(p, tl, tmid, 2 * node + 1, delta);
        update(p, tmid + 1, tr, 2 * node + 2, delta);
        st[node] = st[2 * node + 1] + st[2 * node + 2];
    } // else do nothing
}

int query(int l, int r, int tl, int tr, int node)
{
    if (l == tl && r == tr)
    {
        return st[node];
    }
    else
    {
        int tmid = tl + (tr - tl) / 2;
        if (r <= tmid)
        {
            return query(l, r, tl, tmid, 2 * node + 1);
        }
        else if (l >= tmid + 1)
        {
            return query(l, r, tmid + 1, tr, 2 * node + 2);
        }
        else
        {
            return query(l, tmid, tl, tmid, 2 * node + 1) + query(tmid + 1, tr, tmid + 1, tr, 2 * node + 2);
        }
    }
}

int main()
{
    int n, qnt;
    cin >> n >> qnt;
    int a[n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<vector<int>> q(n);
    vector<pair<int, int>> originalq(qnt);
    int l, r;
    for (int i = 0; i < qnt; i++)
    {
        cin >> l >> r;
        --l;
        --r;
        q[r].emplace_back(l);
        originalq[i] = make_pair(l, r);
    }

    st.resize(4 * n);
    map<int, int> post_last_pos;
    map<pair<int, int>, int> res;
    for (int r = 0; r < n; r++)
    {
        if (post_last_pos[a[r]] == 0) // never found
        {
            update(r, 0, n - 1, 0, 1);
            post_last_pos[a[r]] = r + 1;
        }
        else
        {
            update(post_last_pos[a[r]] - 1, 0, n - 1, 0, -1);
            update(r, 0, n - 1, 0, 1);
            post_last_pos[a[r]] = r + 1;
        }
        for (int l : q[r])
        {
            res[make_pair(l, r)] = query(l, r, 0, n - 1, 0);
        }
    }

    for (auto x : originalq)
    {
        cout << res[x] << '\n';
    }
}