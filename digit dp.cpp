//digit dp
//find numbers in the range [L,R] such that the sum of digits is X
//dp(N,tight,X) counts the number of numbers for N digit number such that sum is X and constraint
int n;
std::vector<int> v;
int dp[19][2][200];
int f(int i,int constraint,int sum){
	if(i==n){
		return (sum==0?1:0);
	}

	if(dp[i][constraint][sum]!=-1){
		return dp[i][constraint][sum];
	}

	int lim=9;
	if(constraint){
		lim=min(lim,v[i]);
	}
	int ans=0;
	for(int digit=0;digit<=lim;digit++){
		if(constraint && digit==lim){
			ans+=f(i+1,constraint,sum-digit);
		}else{
			ans+=f(i+1,0,sum-digit);
		}
	}
	return dp[i][constraint][sum]=ans;
}
int pre(int l,int r,int x){
	memset(dp,-1,sizeof(dp));
	v.clear();
	while(r){
		v.push_back(r%10);
		r/=10;
	}
	reverse(v.begin(),v.end());
	n=v.size();
	int op1=f(0,1,x);
	memset(dp,-1,sizeof(dp));
	l--;
	v.clear();
	while(l){
		v.push_back(l%10);
		l/=10;
	}
	reverse(v.begin(),v.end());
	n=v.size();
	int op2=f(0,1,x);
	return op1-op2;
}

