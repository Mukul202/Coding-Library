vector<int>order;
vector<int>gr[N],grr[N];
int vis[N];
void dfs(int cur){
    vis[cur]=1;
    for(auto x:gr[cur]){
        if(!vis[x])dfs(x);
    }
    order.push_back(cur);
}
vector<int>comp(N);
vector<int>in_comp[N];
void dfs_reverse(int cur,int col){
    comp[cur]=col;
    in_comp[col].push_back(cur);
    vis[cur]=1;
    for(auto x:grr[cur]){
        if(!vis[x])dfs_reverse(x,col);
    }
}
inline void solve(){
    int n,m;
    cin>>n>>m;
    fr(i,m){
        int x,y;
        cin>>x>>y;
        gr[x].pb(y);
        grr[y].pb(x);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            dfs(i);
        }
    }
    int col=1;
    fill(vis,vis+n+1,0);
    for(int i=n;i>=1;i--){
        if(!vis[order[i]])dfs_reverse(order[i],col),col++;
    }
    for(int i=1;i<=n;i++){
        cout<<i<<"->"<<comp[i]<<endl;
    }
  
    for(auto color=2;color<col;color++){
        deb(color);
        for(auto el:in_comp[color]){
            cout<<el<<" ";
        }
        out("");
    }  
}
