vector<int>gr[N];
bool odd_cycle=0;
int vis[N]={0};
void dfs(int cur,int par,int col){
    vis[cur]=col;
    for(auto child:gr[cur]){
        if(vis[child]==0){
            dfs(child,cur,3-col);
        }
        else if(child!=par && col==vis[child]) {
            //backedge
            odd_cycle=1;
        }
    }
    return;
}
