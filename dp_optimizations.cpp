//convex hull trick
const int is_query = -(1LL<<62);
struct line {
  int m, b;
  mutable function<const line*()> succ;
  bool operator<(const line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const line* s = succ();
    if (!s) return 0;
    int x = rhs.m;
    return b - s->b < (s->m - m) * x;
  }
};

struct dynamic_hull : public multiset<line> { // will maintain upper hull for maximum
  const int inf = LLONG_MAX;
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;

    /* compare two lines by slope, make sure denominator is not 0 */
    int v1 = (x->b - y->b);
    if (y->m == x->m) v1 = x->b > y->b ? inf : -inf;
    else v1 /= (y->m - x->m);
    int v2 = (y->b - z->b);
    if (z->m == y->m) v2 = y->b > z->b ? inf : -inf;
    else v2 /= (z->m - y->m);
    return v1 >= v2;
  }
  void insert_line(int m, int b) {
    auto y = insert({ m, b });
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) { erase(y); return; }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }
  int query(int x) {
    auto l = *lower_bound((line) { x, is_query });
    return l.m * x + l.b;
  }
};
dynamic_hull cht;


//divide and conquer DP
int n;
int C(int i,int j);
std::vector<int> dp_before,dp_cur;

//compute dp_cur[l],..dp_cur[r] (inclusive)
void compute(int l,int r,int optl,int optr){
	if(l>r){
		return;
	}
	int mid=l+(r-l)/2;
	pii best={INF,-1};
	for(int k=optl,k<=min(mid,optr);k++){
		best=min(best,{dp_before[k]+C(k,mid),k});
	}
	dp_cur[mid]=best.ff;
	int opt=best.ss;
	compute(l,mid-1,optl,opt);
	compute(mid+1,r,opt,optr);
}

//knuth optimization
//dp(i,j)=mini<=k<=j(f(i,j,k))
//where f(i,j,k)=dp(i,k)+dp(k,j)+cost(i,j)
//breaking string 
int64_t dp[N][N];
int h[N][N];

int Knuth(int m,std::vector<int>&points){
	int n=points.size();
	points.insert(points.begin(),0);
	points.pb(m);
	for(int s=0;s<=n+1;++s){
		for(int l=0;l+s<=n+1;++i){
			int r=l+s;
			if(s<2){
				dp[l][r]=0;
				h[l][r]=l;
				continue;
			}
			dp[l][r]=(1LL<<60);
			for(int k=h[l][r-1];k<=h[l+1][r];++k){
				int cur=dp[l][k]+dp[k][r]+(points[r]-points[l]);
				if(dp[l][r]>cur){
					dp[l][r]=cur;
					h[l][r]=k;
				}
			}
		}
	}
	return dp[0][n+1];
}
