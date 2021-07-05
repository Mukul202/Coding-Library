
//one based indexing
struct fenwicktree
{
      //make tree as :
      //fenwicktree ft(a);
  std::vector<int> bit;
  int n;
      //query as sum(one based index)
  fenwicktree(int n){
    this->n=n+1;
    bit.assign(n+1,0);
  }
  fenwicktree(std::vector<int>&a):fenwicktree(a.size()){
    for(size_t i=0;i<a.size();++i)
      add(i+1,a[i]);
  }
  int sum(int idx){
    int ans=0;
    for(;idx>0;idx-=(idx&-idx))
      ans+=bit[idx];
    return ans;
  }
  int sum(int l,int r){  
    return sum(r)-sum(l-1);
  }
  void add(int idx,int delta){
    for(;idx<n;idx+=(idx&-idx)){
      bit[idx]+=delta;
    }
  }
  void range_add(int l,int r,int val){
        //updates range with val not each element
    add(l,val);
    add(r+1,-val);
  }
};

//2D Fenwick tree
struct fenwick2d
{
  std::vector<std::vector<int>> bit;
  int n,m;
  fenwick2d(int n,int m){
    this->n=n+1;
    this->m=m+1;
    bit.assign(n+1,std::vector<int>(m+1,0));
  }
  fenwick2d(std::vector<std::vector<int>>&a):fenwick2d(a.size(),a[0].size()){
    for(int i=0;i<n;i++){
      for(int j=0;j<m;++j){
        add(i+1,j+1,a[i][j]);
      }
    }
  }
  void add(int x,int y,int val){
    for(int i=x;i<n;i+=(i&-i)){
      for(int j=y;j<m;j+=(j&-j)){
        bit[i][j]+=val;
      }
    }
  }
  int sum(int x,int y){
    int ans=0;
    for(int i=x;i>0;i-=(i&-i)){
      for(int j=y;j>0;j-=(j&-j)){
        ans+=bit[i][j];
      }
    }
    return ans;
  }
};


class BITrangeOperations
{
public:

  ll Tree[MAX+7][2];

  void update(int idx, ll x, bool t)
  {
    while(idx<=MAX)
    {
      Tree[idx][t]+=x;
      idx+=(idx&-idx);
    }
  }
  
  ll query(int idx, bool t)
  {
    ll sum=0;
    while(idx>0)
    {
      sum+=Tree[idx][t];
      idx-=(idx&-idx);
    }
    return sum;
  }
  
  // Returns sum from [0,x]
  ll sum(int x)
  {
    return (query(x,0)*x)-query(x,1);
  }

  void updateRange(int l, int r, ll val)
  {
    update(l,val,0);
    update(r+1,-val,0);
    update(l,val*(l-1),1);
    update(r+1,-val*r,1);
  }

  ll rangeSum(int l, int r)
  {
    return sum(r)-sum(l-1);
  }
};