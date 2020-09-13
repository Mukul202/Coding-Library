template<typename T>
class graph
{
private:
    map<T,list<T>>l;
    map<T, T> par;
    bool visited [N];
    map<T,int>dis;
    vector<T>count;
    int V;
public:
    // graph(int v){
    //     V=v;
    //     count.resize(V+1);
    // }
    void addedge(int x,int y){
        l[x].pb(y);
        l[y].pb(x);
    }
    void bfs(T src){
        queue<T>q;
        q.push(src);
        visited[src]=true;
        dis[src]=0;
        par[src]=-1;
        while(!q.empty()){
            T node=q.front();
            q.pop();
            for(auto nbr:l[node]){
                if(!visited[nbr]){
                    dis[nbr]=dis[node]+1;
                    q.push(nbr);
                    visited[nbr]=true;
                    par[nbr]=node;
                }
            }
        }
    }
    //main dfs function
    void dfs(T src){
        if(visited[src]==true){
            return;
        }
        visited[src]=true;
        cout<<src<<"->";
        for(auto nbr:l[src]){
            dfs(nbr);
        }
    }
    //to get the size of connnected components
    void dfs_helper(T src,int& ans){
        visited[src]=true;
        count[src]=1;
        int mx=1;
        for(auto nbr:l[src]){
            if(!visited[nbr]){
                count[src]+=dfs_helper(nbr,ans);
                mx=max(mx,count[nbr]);
            }
        }
        return count[src];
    }
    //extra function to help 
    void check(){
        for(auto el:l){
            T val=el.ff;
            visited[val]=false;
            count[val]=0;
        }
        dfs_helper(1,ans);
        // deb(ans);
    }
};
