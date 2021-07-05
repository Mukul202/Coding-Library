//modular arithmetic
int add(int x,int y,int m=mod){
	return (x%m + y%m)%m;
}
int sub(int x,int y,int m=mod){
	return (x%m - y%m +m)%m;
}
int mul(int x,int y,int m=mod){
	return ((x%m)*(y%m))%m;
}



const int MAXN=1e6+5;
std::vector<bool> p(MAXN+1, true);
std::vector<int> primes;
void sieve() {
  p[0] = p[1] = false;
  for (int i = 2; i * i <= MAXN; i++)
  {
    if (p[i]) {
      for (int j = i * i; j <= MAXN; j += i) {
        p[j] = false;
      }
    }
  }
  for(int i=2;i<=MAXN;i++){
    if(p[i]){
      primes.pb(i);
    }
  }
}


std::vector<vi>divisors(2006,std::vector<int>(1,1));
void sieve() {
  for (int i = 2; i<= 2005; i ++)
  {
      for (int j = i; j <= 2005; j += i) {
        divisors[j].pb(i);
      }
  }
}

vector<bool> segmentedSieve(long long L, long long R) {
	vector<bool> isPrime(R - L + 1, true);
	long long lim = sqrt(R);
	for (long long i = 2; i <= lim; ++i)
		for (long long j = max(i * i, (L + i - 1) / i * i); j <= R; j += i)
			isPrime[j - L] = false;
	if (L == 1)
		isPrime[0] = false;
	return isPrime;
}

//to get a%m use gcdExtended(a,m,x,y) =x
int gcdExtended(int a, int b, int* x, int* y) 
{ 
    // Base Case 
    if (a == 0)  
    { 
        *x = 0, *y = 1; 
        return b; 
    } 
  
    int x1, y1; // To store results of recursive call 
    int gcd = gcdExtended(b % a, a, &x1, &y1); 
  
    // Update x and y using results of recursive 
    // call 
    *x = y1 - (b / a) * x1; 
    *y = x1; 
  
    return gcd; 
}
int Inverse(int a,int m=mod){
 	int x,y;
 	gcdExtended(a,m,&x,&y);
 	return x;
}



//matrix multiplication
std::vector<std::vector<int>> mult(std::vector<std::vector<int>>& a,vector<std::vector<int>>& b,int m=mod){
  int p=a.size();
  int q=a[0].size();
  int r=b[0].size();
  std::vector<vector<int>> prod(p,std::vector<int> (r,0));
  fr(i,p){
    fr(j,q){
      fr(k,r){
        prod[i][k]+=a[i][j]*b[j][k];
        prod[i][k]%=m;
      }
    }
  }
  return prod;
}
std::vector<std::vector<int>> power(std::vector<std::vector<int>>& a,int n,int p=mod){
  if(n==1){
    return a;
  }
  auto subans=power(a,n/2,p);
  auto ans=mult(subans,subans,p);
  if(n&1LL){
    ans=mult(a,ans,p);
  }
  return ans;
}

std::vector<int> inv(N+1);
void inverse(int m=mod){
  inv[1] = 1;
  for(int i = 2; i < m; ++i)
    inv[i] = m - (m/i) * inv[m%i] % m;
}