#include<bits/stdc++.h>
using namespace std;
int a[1000000];
int st[4000000];
void build(int node, int s, int e)
{
    //leaf node
    if (s == e)
    {
        st[node] = a[s];
    }
    //d&c approach
    int mid = s + ((e - s) >> 1LL);
    build(2 * node, s, mid);
    build(2 * node + 1, mid + 1, e);
    st[node] = min(st[2 * node], st[2 * node + 1]);
}
void update(int node, int s, int e, int i, int val)
{
    //no overlap
    if (i > e || i < s)
    {
        return;
    }
    //leaf node
    if (s == e)
    {
        st[node] = a[s];
        return;
    }
    //partial overlap
    int mid = s + ((e - s) >> 1LL);
    update(2 * node, s, mid, i, val);
    update(2 * node + 1, mid + 1, e, i, val);
    st[node] = min(st[2 * node], st[2 * node + 1]);
}
int query(int node, int s, int e, int l, int r)
{
    //no overlap
    if (s > r || e < l)
    {
        return INT_MAX;
    }
    //complete overlap
    if (s >= l && e <= r)
    {
        return st[node];
    }
    //partial overlap
    int mid = (s + e) / 2;
    int left = query(2 * node, s, mid, l, r);
    int right = query(2 * node + 1, mid + 1, e, l, r);
    return min(left, right);
}
