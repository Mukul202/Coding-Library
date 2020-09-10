int BIT[N]={0};
void update(int i,int inc,int maxn){
    while(i<=maxn){
        BIT[i]+=inc;
        i+=(i&(-i));
    }
}
int query(int i){
    int sum=0;
    while(i>0){
        sum+=BIT[i];
        i-=(i&(-i));
    }
    return sum;
}
int32_t main()
{
    fio;
    cin >> n;
    fr1(i,n){
        cin>>a[i];
        update(i,a[i],n);
    }
    tc{
        int l,r;
        cin>>l>>r;
        out(query(r)-query(l-1));
    }
    printclock;
    return 0;
}
