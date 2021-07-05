//yk=E(aj*wn^kj) for j=0 to n-1
//ak=1/nE(yj*wn^-kj) for j=0 to n-1

using cd=complex<ld>;
const ld PI=acos(-1);
void fft(std::vector<cd>&a,bool invert)
{
	int n=a.size();
	if(n==1){
		return ;
	}
	std::vector<cd>a0(n/2),a1(n/2);
	for(int i=0;2*i<n;++i){
		a0[i]=a[2*i];
		a1[i]=a[2*i+1];
	}
	fft(a0,invert);
	fft(a1,invert);
	ld ang=2*PI/n*(invert?-1:1);
	cd w(1),wn(cos(ang),sin(ang));
	for(int i=0;2*i<n;++i){
		a[i]=a0[i]+w*a1[i];
		a[i+n/2]=a0[i]-w*a1[i];
		if(invert){
			a[i]/=2;
			a[i+n/2]/=2;
		}
		w*=wn;
	}
}
std::vector<int>multiply(std::vector<int>const& a,std::vector<int>const& b)
{
	std::vector<cd>fa(all(a)),fb(all(b));
	int n=1;
	while(n<a.size()+b.size())
		n<<=1LL;
	n<<=1LL;
	fa.resize(n);
	fb.resize(n);
	fft(fa,false);
	fft(fb,false);
	for(int i=0;i<n;++i){
		fa[i]*=fb[i];
	}
	fft(fa,true);
	std::vector<int>result(n);
	for(int i=0;i<n;i++){
		result[i]=int(fa[i].real()+0.5);
	}
	int carry=0;
	for(int i=0;i<n;++i){
		result[i]+=carry;
		carry=result[i]/10;
		result[i]%=10;
	}
	bool flag=0;
	for(int i=n-1;i>=0;i--){
		if(res[i] || flag){
			cout<<res[i];
			flag=true;
		}
	}
	if(!flag){
			cout<<"0";
		}
		out("");
	return result;
}
//in-place computation
using cd=complex<ld>
const ld PI=acos(-1);
int reverse(int num,int lg_n){
	int res=0;
	for(int i=0;i<lg_n;++i){
		if(num&(1LL<<i)){
			res|=(1LL<<(lg_n-1-i));
		}
	}
	return res;
}
void fft(std::vector<cd>&a,bool invert)
{
	int n=a.size();
	for(int i=1,j=0;i<n;i++){
		int bit=(n>>1LL);
		for(;j&bit;bit>>=1LL){
			j^=bit;
		}
		j^=bit;
		if(i<j){
			swap(a[i],a[j]);
		}
	}
	for(int len=2;len<=n;len<<=1LL){
		ld ang=2*PI/len*(invert?-1:1);
		cd wlen(cos(ang),sin(ang));
		for(int i=0;i<n;i+=len){
			cd w(1);
			cd u=a[i+j],v=a[i+j+len/2]*w;
			a[i+j]=u+v;
			a[i+j+len/2]=u-v;
			w*=wlen;
		}
	}
	if(invert){
		for(cd& x:a){
			x/=n;
		}
	}
}

//NTT
const int mod=7340033;
const int root=5;
const int root_1=4404020;//root_1 is the inverse of root modulo mod
const int root_pw=(1LL<<20);

void fft(std::vector<int>&a,bool invert){
	int n=a.size();
	for(int i=1,j=0;i<n;++i){
		int bit=(n>>1LL);
		for(;j&bit;bit>>1LL){
			j^=bit;
		}
		j^=bit;
		if(i<j){
			swap(a[i],a[j]);
		}
	}
	for(int len=2;len<=n;len<<=1LL){
		int wlen=(invert?root_1:root);
		for(int i=len;i<root_pw;i<<=1LL){
			wlen=(int)(1LL*wlen*wlen%mod);
		}
		for(int i=0;i<n;i+=len){
			int w=1;
			for(int j=0;j<len/2;j++){
				int u=a[i+j],v=(int)(1LL*a[i+j+len/2]*w%mod);
				a[i+j]=u+v<mod?u+v:u+v-mod;
				a[i+j+len/2]=u-v>=0?u-v:u-v+mod;
				w=(int)(1LL*w*wlen%mod);
			}
		}
	}
	if(invert){
		int n_1=inverse(n,mod);
		for(int &x:a){
			x=(int)(1LL*x*n_1%mod);
		}
	}
}
