class graph
{
private:
    /* data */int V;
    list<pii>l;
public:
    graph(int V){
        this->V=V;
    }
    void addedge(int u,int v){
        l.push_back(mp(u,v));
    }
    //find function
    int findset(int i,int par[]){
        //path compression
        if(par[i]==-1)
            return i;
        return par[i]=findset(par[i],par);
    }
    void union_set(int x,int y,int par[],int rank[]){
        //union by rank
        auto s1=findset(x,par);
        auto s2=findset(y,par);
        if(s1!=s2){
            if(rank[s1]<rank[s2]){
                par[s1]=s2;
                rank[s2]+=rank[s1];
            }
            else
            {
                par[s2]=s1;
                rank[s1]+=rank[s2];
            }
            
        }
    }
    bool contains_cycle(){
        //dsu logic to check is graph contains cycle or not
        int* par=new int[V];
        int* rank=new int[V];
        fr(i,V){
            par[i]=-1;
            rank[i]=1;
        }
        for(auto edge:l){
            int i=edge.first;
            int j=edge.second;
            int s1=findset(i,par);
            int s2=findset(j,par);
            if(s1!=s2){
                union_set(s1,s2,par,rank);
            }
            else{
                // out("Same parents"<<s1);
                return true;
            }
        }
        delete[] par;
        return false;
    }
};
