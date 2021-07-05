//newest template
template <typename num_t> 
struct segtree {
  int n, depth;
  vector<num_t> tree, lazy;

  void build(int s, long long* arr) {
    n = s;
    tree = vector<num_t>(4 * s, 0);
    lazy = vector<num_t>(4 * s, 0);
    build(0, 0, n - 1, arr);
  }

  num_t build(int i, int l, int r, long long* arr) {
    if (l == r) return tree[i] = arr[l];

    int mid = (l + r) / 2;
    num_t a = build(2 * i + 1, l, mid, arr),
          b = build(2 * i + 2, mid + 1, r, arr);
    return tree[i] = a.op(b);
  }

  void update(int l, int r, num_t v) {
		if (l > r) return;
    update(0, 0, n - 1, l, r, v);
  }
  void update(int index,num_t v){
  	update(0,0,n-1,index,index,v);
  }

  num_t update(int i, int tl, int tr, int ql, int qr, num_t v) {
    eval_lazy(i, tl, tr);
	
	if (tl > tr || tr < ql || qr < tl) return tree[i];
    if (ql <= tl && tr <= qr) {
      lazy[i] = lazy[i].val + v.val;
      eval_lazy(i, tl, tr);
      return tree[i];
    }
    
    if (tl == tr) return tree[i];

    int mid = (tl + tr) / 2;
    num_t a = update(2 * i + 1, tl, mid, ql, qr, v),
          b = update(2 * i + 2, mid + 1, tr, ql, qr, v);
    return tree[i] = a.op(b);
  }

  num_t query(int l, int r) {
	if (l > r) return num_t::null_v;
    return query(0, 0, n-1, l, r);
  }

  num_t query(int i, int tl, int tr, int ql, int qr) {
    eval_lazy(i, tl, tr);
    
    if (ql <= tl && tr <= qr) return tree[i];
    if (tl > tr || tr < ql || qr < tl) return num_t::null_v;

    int mid = (tl + tr) / 2;
    num_t a = query(2 * i + 1, tl, mid, ql, qr),
          b = query(2 * i + 2, mid + 1, tr, ql, qr);
    return a.op(b);
  }

  void eval_lazy(int i, int l, int r) {
    tree[i] = tree[i].lazy_op(lazy[i], (r - l + 1));
    if (l != r) {
      lazy[i * 2 + 1] = lazy[i].val + lazy[i * 2 + 1].val;
      lazy[i * 2 + 2] = lazy[i].val + lazy[i * 2 + 2].val;
    }

    lazy[i] = num_t();
  }
};
struct sum_t {
  long long val;
  static const long long null_v = 0;

  sum_t(): val(0) {}
  sum_t(long long v): val(v) {}

  sum_t op(sum_t& other) {
    return sum_t(val + other.val);
  }
  
  sum_t lazy_op(sum_t& v, int size) {
    return sum_t(val + v.val * size);
  }
};
 
struct max_t {
  long long val;
  static const long long null_v = -9223372036854775807LL;
 	//for min_t remove -
 
  max_t(): val(0) {}
  max_t(long long v): val(v) {}
 
  max_t op(max_t& other) {
    return max_t(max(val, other.val));
  }
  // max_t op(max_t& other) {
  //   return max_t(min(val, other.val));
  // }
  //uncomment it for min_t and remove -
  
  max_t lazy_op(max_t& v, int size) {
    return max_t(val + v.val);
  }
};

//kth zero
const int MAXN=1e6+5;
std::vector<int> st(4*MAXN,0);
int find_kth(int node,int s,int e,int k){
	if(k>st[node])
		return -1;
	if(s==e)
		return s;
	int mid=s+(e-s)/2;
	if(st[2*node]>=k){
		return find_kth(2*node,s,mid,k);
	}	
	return find_kth(2*node+1,mid+1,e,k-st[2*node]);
}

//finding first element greater than x
int st[4*MAXN];
int get_first(int node,int s,int e,int l,int r,int x){
	//no overlap
	if(s>r || e<l)return -1;
	//complete
	if(s>=l and e<=r){
		if(st[node]<=x)
			return -1;
		while(s<=e){
			int mid=s+(e-s)/2;
			if(st[2*node]>x){
				node=2*node;
				e=mid;
			}
			else{
				node=2*node+1;
				s=mid+1;
			}
		}
		return s;
	}

	int mid=s+(e-s)/2;
	int rs=get_first(2*node,s,mid,l,r,x);
	if(rs!=-1)return rs;
	return get_first(2*node+1,mid+1,e,l,r,x);
}


//finding subsegments with maximal sum
struct data
{
	int sum,pref,suf,ans;	
};

data combine(data l,data r)
{
	data res;
	res.sum=l.sum+r.sum;
	res.suf=max(r.suf,r.sum+l.suf);
	res.pref=max(l.pref,l.sum+r.pref);
	res.ans=max(max(l.ans,r.ans),l.suf+r.pref);
}

data make_data(int val)
{
	data res;
	res.sum=val;
	res.pref=res.suf=res.ans=max(0,val);
	return res;
}

void build(std::vector<int>&a,int node,int s,int e)
{
	if(s==e){
		st[node]=make_data(0);
	}else{
		int mid=s+(e-s)/2;
		build(a,2*node,s,mid);
		build(s,2*node+1,mid+1,e);
		st[node]=combine(st[2*node],st[2*node+1]);
	}
}
void update(int node,int s,int e,int index,int val){
	if(s==e){
		st[node]=make_data(val);
	}else{
		int mid=s+(e-s)/2;
		if(index<=mid){
			update(2*node,s,mid,index,val);
		}else{
			update(2*node+1,mid+1,e,index,val);
		}
		st[node]=combine(st[2*node],st[2*node+1]);
	}
}
data query(int node,int s,int e,int l,int r){
	if(l>r){
		return make_data(0);
	}
	if(s==l and r==e){
		return st[node];
	}
	int mid=s+(e-s)/2;
	return combine(query(2*node,s,mid,l,min(r,mid)),query(2*node+1,mid+1,e,max(l,mid+1),r));
}

//finding smallest number greater than or equal to a specified number
std::vector<int> st[4*MAXN];
void build(vi &a,int node,int s,int e){
	if(s==e){
		st[node]=std::vector<int>(1,a[s]);
	}else{
		int mid=s+(e-s)/2;
		build(a,2*node,s,mid);
		build(s,2*node+1,mid+1,e);
		merge(st[2*node].begin(),st[2*node].end(),st[2*node+1],st[2*node+1].end(),back_inserter(st[node]));
	}
}
int query(int node,int s,int e,int l,int r){
	if(l>r){
		return INF;
	}
	if(s==l and r==e){
		auto pos=lower_bound(st[node].begin(),st[node].end(),x);
		if(pos!=st[node].end())
			return *pos;
		return INF;
	}
	int mid=s+(e-s)/2;
	return min(query(2*node,s,mid,l,min(mid,r),x),query(2*node+1,mid+1,e,max(mid+1,l),r,x));
}


//simple 
int n, t[4*MAXN];
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = a[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        t[v] = t[v*2] + t[v*2+1];
    }
}
int sum(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v*2, tl, tm, l, min(r, tm))
           + sum(v*2+1, tm+1, tr, max(l, tm+1), r);
}
void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        t[v] = new_val;
    } else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        else
            update(v*2+1, tm+1, tr, pos, new_val);
        t[v] = t[v*2] + t[v*2+1];
    }
}