
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
int lazy[4*N];
void updateRangeLazy(int node,int s,int e,int l,int r,int inc){
    if(lazy[node]!=0){
        st[node]+=lazy[node];
        if(s!=e){
            lazy[2*node]+=lazy[node];
            lazy[2*node+1]+=lazy[node];
        }
        lazy[node]=0;
    }
    //base case
    //no overlap
    if(s>l or e<r){
        return;
    }
    //rec 2 cases
    //optimization
    if(s>=l and e<=r){
        st[node]+=inc;
        if(s!=e){
            lazy[2*node]+=inc;
            lazy[2*node+1]+=inc;
        }
        return;
    }

    //rec case
    int mid=s+((e-s)>>1LL);
    updateRangeLazy(2*node,s,mid,l,r,inc);
    updateRangeLazy(2*node+1,mid+1,e,l,r,inc);
    st[node]=min(st[2*node],st[2*node+1]);
}
int queryLazy(int node,int s,int e,int l,int r){
    //resolve the lazy value
    if(lazy[node]!=0){
        st[node]+=lazy[node];
        if(s!=e){
            lazy[2*node]+=lazy[node];
            lazy[2*node+1]+=lazy[node];
        }
        lazy[node]=0;
    }
    //base case
    if(s>r or e<l){
        return INT_MAX;
    }

    //complete overlap
    if(s>=l and e<=r){
        return st[node];
    }

    //rec case
    int mid=s+((e-s)>>1LL);
    int left=queryLazy(2*node,s,mid,l,r);
    int right=queryLazy(2*node+1,mid+1,e,l,r);
    return min(left,right);

}
