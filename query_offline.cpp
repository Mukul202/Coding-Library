const  int MAXN=1e6+5;
//MO's Algorithm
struct query
{
  int L;
  int R;
  int q_no;
  int block_no;
  bool operator<(query& other)const
  {
    if(block_no==other.block_no){
      return R<other.R;
    }
    return block_no<other.block_no;
  }
};
int freq[1000005]={0};
int distinct=0;
void add(int elem){
  if(freq[elem]==0){
    distinct++;
  }
  freq[elem]++;
}
void remove(int elem){
  freq[elem]--;
  if(freq[elem]==0){
    distinct--;
  }
}
void adjust(int& cur_l,int& cur_r,query cur_query,std::vector<int>&a){
  while(cur_l<cur_query.L){
    remove(a[cur_l]);
    cur_l++;
  }
  while(cur_l>cur_query.L){
    cur_l--;
    add(a[cur_l]);
  }
  while(cur_r<cur_query.R){
    cur_r++;
    add(a[cur_r]);
  }
  while(cur_r>cur_query.R){
    remove(a[cur_r]);
    cur_r--;
  }
}
void get_ans(std::vector<query>&queries,std::vector<int>& a){
  sort(all(queries));
  memset(freq,0,sizeof(freq));
  distinct=0;
  std::vector<int> ans(queries.size());
  // int n=queries.size();
  for(int i=queries[0].L;i<=queries[0].R;i++){
    add(a[i]);
  }
  int last_l=queries[0].L;
  int last_r=queries[0].R;
  ans[queries[0].q_no]=distinct;
  for(int i=1;i<queries.size();i++){
    adjust(last_l,last_r,queries[i],a);
    ans[queries[i].q_no]=distinct;
  }
  for(auto el:ans){
    cout<<el<<"\n";
  }
}


//SQRT decomposition
void query(std::vector<pii>&queries,std::vector<int>&a){
	int n=a.size();
	std::vector<int> ans(queries.size());
	int len=(int)sqrt(n+.0)+1;
	std::vector<int>blocks(len);
	for(int i=0;i<n;i++)
		blocks[i/len]+=a[i];
	for(int i=0;i<queries.size();++i){
		int l=queries[i].ff;
		int r=queries[i].ss;
		int sum=0;
		int block_l=l/len,block_r=r/len;
		if(block_l==block_r){
			for(int i=l;i<=r;i++){
				sum+=a[i];
			}
		}
		else{
			for(int i=l,end=(block_l+1)*len-1;i<=end;++i){
				sum+=a[i];
			}
			for(int i=block_l+1;i<=block_r-1;++i){
				sum+=blocks[i];
			}
			for(int i=block_r*len;i<=r;++i){
				sum+=a[i];
			}
		}
	}
}


//Sparse Table 
//query based on 0 indexing 
const int MAXN=2e5+5;
//range sum query
const int K=25;
int st[MAXN][K+1];
void pre(std::vector<int>&a)
{
  int n=a.size();
  for(int i=0;i<n;++i){
    st[i][0]=a[i];
  }
  for(int j=1;j<=K;++j){
    for(int i=0;i+(1LL<<j)<=n;++i){
      st[i][j]=st[i][j-1]+st[i+(1LL<<(j-1))][j-1];
    }
  }
}
int query(int L,int R)
{
  int sum=0;
  for(int j=K;j>=0;j--){
    if((1LL<<j)<=(R-L+1)){
      sum+=st[L][j];
      L+=(1LL<<j);
    }
  }
  return sum;
}

//Range Min Query,Max Query,GCD
const int MAXN=1e6+5;
const int K=25;
int st[N][K+1];
int lg[N+1];
void pre(std::vector<int>const& a)
{
  int n=a.size();
  for(int i=0;i<n;++i){
    st[i][0]=a[i];
  }
  for(int j=1;j<=K;j++){
    for(int i=0;i+(1LL<<j)<=n;++i){
      st[i][j]=min(st[i][j-1],st[i+(1LL<<(j-1))][j-1]);
    }
  }
  lg[1]=0;
  for(int i=2;i<=N;i++){
    lg[i]=lg[i/2]+1;
  }
}
int query(int L,int R){
  int j=lg[R-L+1];
  int minimum=min(st[L][j],st[R-(1LL<<j)+1][j]);
  return minimum;
}