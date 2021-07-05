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

std::vector<int> inv(N+1);
void get_inv(int m=mod){
	inv[1]=1;
	for(int i=2;i<m;++i){
		inv[i]=m-(m/i)*inv[m%i]%m;
	}
}

std::vector<int> factorial(N+1);
void fact(int m=mod){
  factorial[0] = 1;
  for (int i = 1; i <= N; i++) {
      factorial[i] = factorial[i - 1] *i;
      factorial[i]%=m;
  }
}
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
  x=(x%m+m)%m;
  return x;
}
int inverse_factorial(int n,int m=mod){
  return Inverse(factorial[n],m);
}
long long binomial_coefficient(int n, int k,int m=mod) {
    return mul(factorial[n],mul(inverse_factorial(k),inverse_factorial(n-k),m),m);
}

int C[1006][1006];
int binomialCoeff(int n, int k)
{
    int i, j;
 
    // Caculate value of Binomial Coefficient
    // in bottom up manner
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= min(i, k); j++) {
            // Base Cases
            if (j == 0 || j == i){
                C[i][j] = 1;
                C[i][j]%=mod;
            }
 
            // Calculate value using previously
            // stored values
            else{
                C[i][j] =C[i - 1][j - 1] + C[i - 1][j];
                C[i][j]%=mod;
            }
        }
    }
 
    return C[n][k];
}

//catalan numbers
int cat(int n){
  int catalan[n+1];
  catalan[0]=catalan[1]=1;
  for(int i=2;i<=n;++i){
    catalan[i]=0;
    for(int j=0;j<i;j++){
      catalan[i]+=catalan[j]*catalan[i-j-1];
    }
  }
  return catalan[n];
}