int dp[105][105];
//MATRIX Chain Multiplication
int sum[105];
int get(int s,int e){
    if(s==0)
      return sum[e];
    return (100+sum[e]-sum[s-1])%100;
}
int solve(int i,int j){
    if(i>=j){
        return 0;
    }   
 
    //check in dp
    if(dp[i][j]!=-1){
        return dp[i][j];
    }
 
    //rec case
    int ans=INT_MAX;
    for(int k=i;k<j;k++){
        ans=min(ans,solve(i,k)+solve(k+1,j)+get(i,k)*get(k+1,j));
    }
    return dp[i][j]=ans;
}

//actual MCM
//ans is f(1,n-1)
int f(int i,int j){
  if(i>=j)
    return 0;
  if(dp[i][j]!=-1)
    return dp[i][j];
  int ans=inf;
  for(int k=i+1;k<j;++k){
    ans=min(ans,f(i,k)+f(k+1,j)+a[i-1]*a[k]*a[j]);
  }
  return dp[i][j]=ans;
}


//SOS dp
std::vector<vi> dp(21,std::vector<int>((1LL<<22),-1));
std::vector<vi> a;
int n;
int f(int i,int subset){
  //counts the no. of ways to pair i..n-1 men with given subset
  if(i==n-1){
    int cnt=0;
    for(int j=0;j<n;j++){
      int mask=(1LL<<j);
      int bit=(subset&mask);
      if(a[i][j]==1 and bit){
        cnt++;
        if(cnt>mod){
          cnt%=mod;
        }
      }
    }
    return dp[i][subset]=cnt;
  }

  //check
  if(dp[i][subset]!=-1){
    return dp[i][subset];
  }


  int cnt=0;
  for(int j=0;j<n;j++){
    int mask=(1LL<<j);
    int bit=(subset&mask);
    if(a[i][j]==1 and bit){
      //clearbit jth
      // int new_mask=(~(1LL<<j));
      int new_subset=(subset^mask);
      cnt+=f(i+1,new_subset);
      if(cnt>=mod){
        cnt%=mod;
      }
    }
  }
  return dp[i][subset]=cnt;
}


//DP on trees
std::vector<int> graph[N];
std::vector<vi> dp(N,std::vector<int>(2,-1));
int f(int node,int bound,int par){
  //check
  if(dp[node][bound]!=-1)
    return dp[node][bound];

  //rec case
  int ans=0;
  int op1=1;
    for(auto child:graph[node]){
      if(child==par)
        continue;
      op1*=f(child,0,node);
      op1%=mod;
    }
    ans+=op1;
    ans%=mod;
  if(!bound){
    //anything can be painted
    int op2=1;
    for(auto child:graph[node]){
      if(child==par)
        continue;
      op2*=f(child,1,node);
      op2%=mod;
    }
    ans+=op2;
    ans%=mod;
  }
  
  return dp[node][bound]=ans;
}

//sequence based DP
//always think of dp[i] as the sequence ending at ith position
 //Q of atcoder (dp+binary_search using lower_bound)
map<int,int>useful;
std::vector<int> dp(n+1);
dp[0]=0;
dp[1]=a[1].beauty;
useful[a[1].height]=dp[1];
int ans=dp[1];
for(int i=2;i<=n;++i){
  dp[i]=a[i].beauty;
  auto it=useful.lower_bound(a[i].height+1);
  if(it!=useful.begin())
  {
    it--;
    dp[i]+=it->second;
    it++;
  }
  useful[a[i].height]=dp[i];
      // it=useful.upper_bound(a[i].height);
  while((it!=useful.end()) and (it->first>a[i].height) and (it->second<=dp[i])){
    auto temp=it;
    temp++;
    useful.erase(it);
    it=temp;
  }
  ans=max(ans,dp[i]);
}


//S: DIGIT DP+modular arithmetic
string k;
int D;
std::vector<std::vector<vi>> dp(N,std::vector<vi>(105,std::vector<int>(2,-1)));
int f(int index,int d,int bound){
  //f(index,d,bound) counts the number of numbers to form sum%D=d from index...n-1
  if(index==k.size()){
    return (d==0);
  }

  //check
  if(dp[index][d][bound]!=-1){
    return dp[index][d][bound];
  }
  //
  int end=(bound?(k[index]-'0'):9);
  int ans=0;
  for(int i=0;i<=end;i++){
    if(bound && i==end){
      ans+=f(index+1,(D+d-i%D)%D,1);
    }else{
      ans+=f(index+1,(D+d-i%D)%D,0);
    }
    ans%=mod;
  }
  return dp[index][d][bound]=ans;
}

//T Recurrence dp
//O(n^3)->O(n^2)
std::vector<vi>dp(3005,std::vector<int> (3005));
void f(string& s,int n){
  //dp[i][g] calculates the number of ways such that there are g numbers greater than 
  //the number placed at i-1th place
  dp[n][0]=(s[n-2]=='>'?1:0);
  dp[n][1]=(s[n-2]=='<'?1:0);
  for(int i=n-1;i>=2;i--){
    int total=n-i+1;
    for(int g=0;g<=total;g++){
      if(i==n and g==0)
        continue;
      if(g==0)
      {
        dp[i][g]=0;
        if(s[i-2]=='<')
          continue;
        for(int j=1;j<=total;j++)
        {
          dp[i][g]=add(dp[i][g],dp[i+1][total-j]);
        }
      }
      else
      {
        if(s[i-2]=='>')
        {
          dp[i][g]=sub(dp[i][g-1],dp[i+1][g-1]);
        }
        else
        {
          dp[i][g]=add(dp[i][g-1],dp[i+1][g-1]);
        }
      }
    }
  }
}

//U Bitmasks+DP
std::vector<int>dp((1LL<<16),-1);
std::vector<int>sum((1LL<<16),0);
int n;
void gen_sum(std::vector<vi>const& a){
  for(int i=1;i<(1LL<<n);++i){
    std::vector<int> rabbits;
    for(int j=0;j<n;j++){
      int mask=(1LL<<j);
      if(mask&i)
      {
        rabbits.pb(j);
      }
    }
    for(int k=0;k<rabbits.size();k++){
      for(int j=k+1;j<rabbits.size();++j){
        sum[i]+=a[rabbits[k]][rabbits[j]];
      }
    }
  }
}
int f(int subset){
  //f(subset) calculates the maximum score we can get from cur subset
  if(subset==0){
    return 0;
  } 

  //check
  if(dp[subset]!=-1)
    return dp[subset];

  //rec case
  int ans=0;
  for(int mask=subset;mask!=0;mask=(mask-1)&subset){
    ans=max(ans,sum[mask]+f(subset^mask));
  }
  return dp[subset]=ans;
}

//Kadane's algorithm
int Kadane(std::vector<int>const&a){
  //use when to find the pos for which it gives min respect to current index
  int n=a.size();
  int sum=0,ans=a[0];
  int ans_l=0,ans_r=0,min_pos=-1;
  for(int i=0;i<n;i++){
    sum+=a[i];
    if(sum>ans)
    {
      ans=sum;
      ans_r=i;
      ans_l=min_pos+1;
    }
    if(sum<0)
    { 
      sum=0;
      min_pos=i;
    }
  }
  return ans;
}

//LIS
int lis(std::vector<int>const&a){
  int n=a.size();
  const int INF=1e9;
  std::vector<int>d(n+1,INF);
  //d[i] stores the element optimal for LIS with length i
  d[0]=-INF;
  for(int i=0;i<n;i++){
    int j=upper_bound(d.begin(),d.end(),a[i])-d.begin();
    if(d[j-1]<a[i] && a[i]<d[j]){
      d[j]=a[i];
    }
  }
  int ans=0;
  for(int i=0;i<=n;++i){
    if(d[i]<INF){
      ans=i;
    }
  }
  std::vector<int> restoring_seq;
  for(int i=1;i<=ans;++i){
    restoring_seq.push_back(d[i]);
  }
  return ans;
}

//partition subset sum
bool canPartition(std::vector<int>const& a){
  int n=a.size();
  int sum=0;
  for (int i = 0; i < n; ++i)
  {
    sum+=a[i];
  }
}

//LCS
int LCS(string &s,string &t){
  int n=s.size();
  int m=t.size();
  std::vector<std::vector<int>> dp(n+1,std::vector<int>(m+1,0));
  for(int i=0;i<=n;i++){
    for(int j=0;j<=m;j++){
      if(i==0 or j==0){
        dp[i][j]=0;
      }
      else if(s[i-1]==t[j-1]){
        dp[i][j]=dp[i-1][j-1]+1;
      }
      else{
        dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
      }
    }
  }
  return dp[n][m];
}


//DIGIT DP 
//find numbers in the range [L,R] such that sum of the digits is X
