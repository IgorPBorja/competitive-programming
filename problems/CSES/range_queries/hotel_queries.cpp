#include <bits/stdc++.h>
using namespace std;

/*
we want two functionalities
1. for each r_i we want to find the first index j such that hotel j has more than
or exactly r_i rooms
2. we want to decrease number of rooms in hotel j by r_i 

this can be done in O((N + Q) log N) using a lower bound segment tree
*/

const int INF = 2e9;

// return index in the tree and in the array
pair<int, int> lb_query(int maxST[], int x, int l, int r, int node = 0)
{
    if (l + 1 == r)
    {
        // unitary interval
        if (maxST[node] >= x) 
            return make_pair(l, node);
        else 
            return make_pair(INF, INF); 
    } else  
    {
        int mid = l + (r - l)/2;
        if (maxST[2*node + 1] >= x)
        {
            return lb_query(maxST, x, l, mid, 2*node + 1);
        } else if (maxST[2*node + 2] >= x)
        {
            return lb_query(maxST, x, mid, r, 2*node + 2);
        } else 
        {
            return make_pair(INF, INF);
        }
    }
}

void build(int maxST[], int a[], int l, int r, int curr_node = 0)
{
    if (l + 1 == r)
    {
        maxST[curr_node] = a[l];
    } else
    {
        int mid = l + (r - l)/2;
        build(maxST, a, l, mid, 2*curr_node + 1);
        build(maxST, a, mid, r, 2*curr_node + 2);
        maxST[curr_node] = max(maxST[2*curr_node + 1], maxST[2*curr_node + 2]);
    }
}

void update(int maxST[], int pos, int x, int l, int r, int curr_node = 0)
{
    // case 1: unitary
    if (l + 1 == r && l == pos)
    {
        maxST[curr_node] = x;
    } else if (l <= pos && pos < r)
    {
        int mid = l + (r - l) / 2;
        if (pos < mid) update(maxST, pos, x, l, mid, 2*curr_node + 1);
        else if (pos >= mid) update(maxST, pos, x, mid, r, 2*curr_node + 2);
        maxST[curr_node] = max(maxST[2*curr_node + 1], maxST[2*curr_node + 2]);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    int a[n], maxST[4*n];
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    build(maxST, a, 0, n);
    
    int rooms;
    for (int i = 0; i < m; i++)
    {
        cin >> rooms;
        auto [array_index, node_index] = lb_query(maxST, rooms, 0, n);
        if (array_index == INF)
        {
            cout << 0 << ' ';
        } else 
        {
            cout << array_index + 1 << ' '; // 1-indexed positions!!
            update(maxST, array_index, maxST[node_index] - rooms, 0, n);
            // you can't use a[array_index] - rooms as value
            // otherwise updating the same position twice won't have the cumulative effect
            // (the path will be x -> x - r_i -> x - r_j instead
            // of x -> x - r_i -> x - r_i - r_j)
        }
    }
}

