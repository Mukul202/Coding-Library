#include<bits/stdc++.h>
using namespace std;
#define MAXN 100005
int tree[4*MAXN+1];
int a[MAXN];
//1-based indexing
void build(int node,int s,int e){
    //leaf node
    if(s==e){
        tree[node]=a[s];
    }
    //d&c approach
    int mid=s+((e-s)>>1LL);
    build(2*node,s,mid);
    build(2*node+1,mid+1,e);
    tree[node]=min(tree[2*node],tree[2*node+1]);
}
void update(int node,int s,int e,int i,int val){
    //no overlap
    if(i>e || i<s){
        return;
    }
    //leaf node
    if(s==e){
        tree[node]=a[s];
        return;
    }
    //partial overlap
    int mid=s+((e-s)>>1LL);
    update(2*node,s,mid,i,val);
    update(2*node+1,mid+1,e,i,val);
    tree[node]=min(tree[2*node],tree[2*node+1]);
}
int query(int node,int s,int e,int l,int r){
    //no overlap
    if(s>r || e<l){
        return INT_MAX;
    }
    //complete overlap
    if(s>=l && e<=r){
        return tree[node];
    }
    //partial overlap
    int mid=(s+e)/2;
    int left=query(2*node,s,mid,l,r);
    int right=query(2*node+1,mid+1,e,l,r);
    return min(left,right);
}
