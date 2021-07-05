//coordinate compression
void compress(std::vector<int>&a){
	std::vector<int> b(all(a));
	sort(all(b));
	map<int,int>m;
	map<int,int>back;
	int index=1;
	fr(i,n){
		if(!m[b[i]]){
			m[b[i]]=index;
			back[index]=b[i];
			index++;
		}
	}
	fr(i,n){
		a[i]=m[a[i]];
	}
}

//interpolation search
//works best for uniformly distributed cases O(log(log(n))) but in worst case O(n)
int interpolation(std::vector<int>&a,int key)
{
	int n=a.size();
	int lo=0;hi=n-1;
	while(lo<=hi and key>=a[lo] and key<=a[hi]){
		if(lo==hi){
			if(a[lo]==key){
				return lo;
			}
			return -1;
		}
		int pos=lo+(((double)(hi-lo)/(a[hi]-a[lo]))*(key-a[lo]));
		if(a[pos]==key){
			return pos;
		}
		if(a[pos]<key){
			lo=pos+1;
		}else{
			hi=pos-1;
		}
	}
	return -1;
}

//exponential search
int exponential(std::vector<int>&a,int key){
	if(a[0]==key){
		return 0;
	}
	int n=a.size();
	int i=1;
	while(i<n and a[i]<=key)
		i=(i<<1LL);
	int lo=i/2;
	int hi=min(i,n-1);
	while(lo<=hi){
		int mid=lo+(hi-lo)/2;
		if(a[mid]==key){
			return mid;
		}else if(a[mid]<key){
			lo=mid+1;
		}else{
			hi=mid-1;
		}
	}
	return -1;
}

//ternary search
double ternary_search(double l,double r){
	//this is to find the condition of max answer
	double eps=1e-9;
	while(r-l>eps){
		double m1=l+(r-l)/3;
		double m2=r-(r-l)/3;
		double f1=f(m1);
		double f2=f(m2);
		if(f1<f2){
			l=m1;
		}else{
			r=m2;
		}
	}
	return f(l);
}