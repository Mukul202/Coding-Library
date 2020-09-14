int shortest(int n){
    int ans=INT_MAX;
    fr(i,n){
        vector<int>dis(n,(INT_MAX));
        vector<int>par(n,-1);
        dis[i]=0;
        queue<int>q;
        q.push(i);
        while(!q.empty()){
            int node=q.front();
            q.pop();
            for(auto child:gr[node]){
                if(dis[child]==INT_MAX){
                    dis[child]=dis[node]+1;
                    par[child]=node;
                    q.push(child);
                }   
                else if(par[child]!=node and par[node]!=child){
                    //backedge
                    ans=min(ans,dis[node]+dis[child]+1);
                }
            }
        }
    }
    return ans;
}
