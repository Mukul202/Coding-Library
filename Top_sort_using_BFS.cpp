#include<bits/stdc++.h>
using namespace std;
template<typename T>
class Graph{
    list<T>*l;
    int v;
public:
    Graph(int v){
        this->v=v;
        l=new list<T>[v];
    }
    void addedge(T x,T y){
        l[x].push_back(y);
    }
    void top_sort(){
        int *indeg=new int[v];
        for(int i=0;i<v;i++){
            indeg[i]=0;
        }
        //update indegree by traversing edges x->y
        for(int i=0;i<v;i++){
            for(auto y:l[i]){
                indeg[y]++;
            }
        }

        queue<T>q;
        for(int i=0;i<v;i++){
            if(indeg[i]==0){
                q.push(i);
            }
        }
        while(!q.empty()){
            T node=q.front();
            cout<<node<<" ";
            q.pop();
            for(auto nbr:l[node]){
                indeg[nbr]--;
                if(indeg[nbr]==0){
                    q.push(nbr);
                }
            }
        }
        delete(indeg);
    }

};
int main(){
    int n;
    cin>>n;
    Graph<int>g(n+1);
    g.addedge(0,2);
    g.addedge(1,2);
    g.addedge(2,3);
    g.addedge(3,5);
    g.addedge(4,5);
    g.addedge(1,4);
    g.addedge(2,5);
    g.top_sort();
    return 0;
}
