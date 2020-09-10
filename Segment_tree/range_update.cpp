int a[N];
int n, m;
vector<int> graph[N];
int st[400005];

//1-based indexing of nodes
void build(int node, int s, int e)
{
    //leaf node
    if (s == e)
    {
        st[node];
        return;
    }
    //d&c approach
    int mid = s + ((e - s) >> 1LL);
    build(2 * node, s, mid);
    build(2 * node + 1, mid + 1, e);
    st[node]=min(st[2*node],st[2*node+1]);
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
void updateRange(int node,int s,int e,int l,int r,int val){
    if(l>e || r<s)
        return;
    if(s==e){
        st[node]=val;
        return;
    }
    int mid=s+((e-s)>>1LL);
    updateRange(2*node,s,mid,l,r,val);
    updateRange(2*node+1,mid+1,e,l,r,val);
    st[node]=min(st[2*node],st[2*node+1]);
}
int query(int node, int s, int e, int l, int r,int k)
{
    //no overlap
    if (s > r || e < l)
    {
        return 0;
    }
    //complete overlap
    if (s >= l && e <= r)
    {
        return st[node];
    }
    //partial overlap
    int mid = (s + e) / 2;
    int left = query(2 * node, s, mid, l, r,k);
    int right = query(2 * node + 1, mid + 1, e, l, r,k);
    return min(left,right);
}
