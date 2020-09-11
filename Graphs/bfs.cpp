template<typename T>
class graph
{
private:
    map<T,list<T>>l;
    map<T,T>one;
    /* data */
public:
    void addedge(int x,int y,bool bi_dir=false){
        l[x].pb(y);
        if(bi_dir){
            l[y].pb(x);
        }
    }
    void bfs(T src){
        map<T,int>visited;
        queue<T>q;
        q.push(src);
        visited[src]=true;
        while(!q.empty()){
            T node=q.front();
            cout<<node<<"->";
            q.pop();
            for(int nbr:l[node]){
                if(!visited[nbr]){
                    q.push(nbr);
                    visited[nbr]=true;
                }
            }
        }
    }
    void dis(T src,T des){
        map<T,bool>visited;
        map<T,int>dis;
        queue<T>q;
        q.push(src);
        dis[src]=0;
        map<T,T>par;
        par[src]=-1;
        visited[src]=true;
        while(!q.empty()){
            T node=q.front();
            q.pop();
            for(int nbr:l[node]){
                if(!visited[nbr]){
                    q.push(nbr);
                    dis[nbr]=dis[node]+1;
                    par[nbr]=node;
                    visited[nbr]=true;
                }
            }
        }
        cout<<"min distance is "<<dis[des]<<"\n";
        while(par[des]!=-1){
            cout<<des<<"<-";
            des=par[des];
        }
        cout<<src<<"\n";
    }
    
};
