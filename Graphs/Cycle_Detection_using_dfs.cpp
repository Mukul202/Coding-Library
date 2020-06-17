#include<bits/stdc++.h>
using namespace std;
template<typename T>
class Graph
{
private:
    /* data */
    int v;
    list<T>*l;
public:
    Graph(int v){
        this->v=v;
        l=new list<T>[v];
    }
    void addedge(T x,T y,bool directed=true){
        l[x].push_back(y);
        if(!directed){
            l[y].push_back(x);
        }
    }
    bool cycle_detector(T node,bool *visited,bool *stack){
        visited[node]=true;
        stack[node]=true;

        for(auto nbr:l[node]){
            //two cases
            if(stack[nbr]==true){
                //backedge
                return true;
            }
            if(!visited[nbr]){
                bool cycle_mila=cycle_detector(nbr,visited,stack);
                if(cycle_mila){
                    return true;
                }
            }
        }

        //leave the node
        stack[node]=false;
        return false;
    }
    bool contains_cycle(){
        bool *visited=new bool[v];
        bool *stack=new bool[v];
        for(int i=0;i<v;i++){
            visited[i]=stack[i]=false;
        }
        return cycle_detector(0,visited,stack);
    }

};
int main(){
    Graph<int>g(7);
    g.addedge(0,1);
    g.addedge(1,2);
    g.addedge(2,3);
    g.addedge(3,4);
    g.addedge(4,5);
    g.addedge(1,5);
    g.addedge(5,6);
    g.addedge(4,2);
    cout<<(g.contains_cycle()?"Yes":"NO");
    return 0;
}
