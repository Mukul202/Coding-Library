class graph
{
private:
    /* data */int V;
    list<int>*l;
public:
    graph(int v){
        V=v;
        l=new list<int>[V];
    };
    void addedge(int u,int v){
        l[u].push_back(v);
        l[v].push_back(u);
    }
    bool cycle_helper(int node,bool* visited,int par){
        visited[node]=true;
        for(auto nbr:l[node]){
            if(!visited[nbr]){
                bool cycle_mila= cycle_helper(nbr,visited,node);
                if(cycle_mila)
                    return true;
            }
            else{
                if(nbr==par){
                    continue;
                }
                else 
                    return true;
            }
        }
        return false;
    }
    bool contains_cycle(int node,int parent){
        bool* visited=new bool[V]{false};
        return cycle_helper(0,visited,-1);
    }
};
