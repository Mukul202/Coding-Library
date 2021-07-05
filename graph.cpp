// DFS
std::vector<int> graph[N];
std::vector<bool> vis(N, false);
void dfs(int node) {
  vis[node] = true;
  for (auto nbr : graph[node]) {
    if (!vis[nbr])
      dfs(nbr);
  }
}


// BFS
void bfs(int src, int n) {
  queue<int>q;
  q.push(src);
  std::vector<bool> vis(n + 1, false);
  std::vector<int> par(n+1,-1);
  std::vector<int> dis(n + 1, inf);
  par[src] = -1;
  dis[src] = 0;
  vis[src]=true;
  while (!q.empty()) {
    auto node = q.front();
    q.pop();
    for (auto nbr : graph[node]) {
      if (!vis[nbr]) {
        dis[nbr] = dis[node] + 1;
        q.push(nbr);
        par[nbr] = node;
        vis[nbr]=true;
      }
    }
  }
  
  if(!vis[des]){
    cout<<"NO Path";
  }
  else{
    vector<int>path;
    for(int u=des;u!=-1;u=par[u]){
      path.pb(u);
    }
    reverse(all(path));
  }
  
}

//other form of BFS
void bfs(int src,int n){

  //for all forming paths
  queue<int>q;
  std::vector<bool> vis(n+1,false);
  std::vector<int>dis(n+1,INF);
  std::vector<int>par[n+1];
  q.push(src);
  while(!q.empty()){
    auto node=q.front();
    q.pop();
    if(vis[node])
      continue;
    vis[node]=true;
    for(auto nbr:graph[node]){
      if(!vis[nbr]){
        q.push(nbr);
        if(dis[nbr]>=dis[node]+1){
          par[nbr].pb(node);
          dis[nbr]=dis[node]+1;
        }
      }
    }
  }
  if(dis[des]==INF){
    return -1;
  }else{
    //form the paths
  }
}

//DSU
std::vector<int> par;
std::vector<int> size;
int find(int u) {
  if (par[u] == u)
    return u;
  return par[u] = find(par[u]);
}
void merge_sets(int s1, int s2) {
  int p1 = find(s1);
  int p2 = find(s2);
  if (p1 != p2) {
    if (size[p1] >= size[p2]) {
      par[p2] = p1;
      size[p1] += size[p2];
    }
    else {
      par[p1] = p2;
      size[p2] += size[p1];
    }
  }
}

//KRUSKAL
//here we have to make an array of pair<int,pair<int,int>> with weight and edge
struct Edge
{
  int u, v, weight;
  bool operator<(Edge const& other) {
    return weight < other.weight;
  }
};
int kruskal(std::vector<Edge>& edges, int n) {
  int cost = 0;
  sort(all(edges));
  std::vector<int> res;
  par.resize(n + 1);
  size.resize(n + 1);
  for (int i = 0; i <= n; i++) {
    par[i] = i;
    size[i] = 1;
  }
  for (auto edge : edges) {
    int u = edge.u;
    int v = edge.v;
    if (find(u) != find(v)) {
      cost += edge.weight;
      res.pb(u);
      merge_sets(u, v);
    }
  }
  return cost;
}

//PRIM
std::vector<pii> graph[N + 1];
int prim(int src) {
  //graph[i] indicates {v,weight}
  int ans = 0;
  priority_queue<pii, std::vector<pii>, greater<pii>>q;
  q.push({0, src});
  while (!q.empty()) {
    auto node = q.top().ss;
    auto weight = q.top().ff;
    q.pop();
    if (vis[node])
      continue;
    ans += weight;
    for (auto edge : graph[node]) {
      auto nbr = edge.ff;
      auto weight_edge = edge.ss;
      if (!vis[nbr]) {
        q.push({weight_edge, nbr});
      }
    }
  }
  return ans;
}


//TOPSORT
bool vis[N] = {0};
std::vector<int> graph[N];
int indeg[N] = {0};
bool cur[N] = {0};
bool has_cycle(int node) {
  vis[node] = true;
  cur[node] = true;
  for (int nbr : graph[node]) {
    if (!vis[nbr] and has_cycle(nbr)) {
      return true;
    }
    else if (cur[nbr])return true;
  }
  cur[node] = false;
  return false;
}
void top_sort(int n) {
  //nodes in 1-based indexing
  for (int i = 0; i <= n; i++) {
    for (int v : graph[i]) {
      indeg[v]++;
    }
  }
  min_pq q;//it sorts in lexicographical order
  //otherwise use queue
  for (int i = 1; i <= n; i++) {
    if (indeg[i] == 0) {
      q.push(i);
    }
  }
  vi ans;
  while (!q.empty()) {
    auto node = q.top();
    q.pop();
    ans.pb(node);
    for (auto nbr : graph[node]) {
      indeg[nbr]--;
      if (indeg[nbr] == 0)
        q.push(nbr);
    }
  }
  if(ans.size()!=n){
    out("NO cycle");
  }
  for (auto el : ans) {
    cout << el << " ";
  }
}


//cycle
std::vector<bool> vis(N + 1, false);
std::vector<int> graph[N];
bool has_cycle(int node, int par) {
  vis[node] = true;
  for (auto nbr : graph[node]) {
    if (!vis[nbr]) {
      if (has_cycle(nbr, node))
        return true;
    }
    else if (nbr != par) {
      return true;
    }
  }
  return false;
}

//dijkitra O(n^2)
const int INF=1000000000;
std::vector<std::vector<pii>> graph;
void dijkitra(int src,std::vector<int>&d,std::vector<int>&p){
  int n=graph.size();
  d.assign(n+1,INF);
  p.assign(n+1,-1);
  std::vector<bool> vis(n+1,false);
  d[src]=0;
  for(int i=0;i<n;++i){
    int node=-1;
    for(int j=0;j<n;++j){
      if(!vis[j] and (v==-1 || d[j]<d[node]))
        node=j;
    }
    if(d[node]==INF)
      break;
    vis[node]=true;
    for(auto edge:graph[node]){
      int nbr=edge.ff;
      int weight=edge.ss;
      if(d[node]+weight<d[nbr]){
        d[nbr]=d[node]+weight;
        p[nbr]=node;
      }
    }
  }
}
std::vector<int> restore_path(int s,int t,std::vector<int>const& p){
  std::vector<int> path;
  for(int v=t;v!=s;v=p[v]){
    path.pb(v);
  }
  path.pb(s);
  reverse(all(path));
  return path;
}


//dijkitra O(mlogn)
//set edition
const int INF=10000000000;
std::vector<std::vector<pii>> graph;
void dijkitra(int src,int n,std::vector<int>&d,std::vector<int>&p){
  d.assign(n+1,INF);
  p.assign(n+1,-1);
  d[src]=0;
  set<pii>q;
  q.insert({0,src});
  while(!q.empty()){
    int node=q.begin()->ss;
    q.erase(q.begin());
    for(auto edge:graph[node]){
      int nbr=edge.ff;
      int weight=edge.ss;
      if(d[node]+weight<d[nbr]){
        q.erase({d[nbr],nbr});
        d[nbr]=d[node]+weight;
        p[nbr]=node;
        q.insert({d[nbr],nbr});
      }
    }
  }
}

//priority_queue
const int INF=10000000000;
std::vector<std::vector<pii>> graph;
void dijkitra(int src,int n,std::vector<int>&d,std::vector<int>&p){
  d.assign(n+1,INF);
  p.assign(n+1,-1);
  d[src]=0;
  priority_queue<pii,std::vector<pii>,greater<pii>>q;
  q.push({0,src});
  while(!q.empty()){
    int node=q.top().ss;
    int d_node=q.top().ff;
    q.pop();
    if(d_node!=d[node]){
      continue;
    }
    for(auto edge:graph[node]){
      int nbr=edge.ff;
      int weight=edge.ss;
      if(d[node]+weight<d[nbr]){
        d[nbr]=d[node]+weight;
        p[nbr]=node;
        q.push({d[nbr],nbr});
      }
    }
  }
}


//euler tour
std::vector<int> g[N+1];
std::vector<int> in(N+1);
vi op(N+1);
int tim=0;
std::vector<int> a;
std::vector<int> euler_tour(1,0);
void dfs(int u,int par=-1)
{
  in[u]=++tim;
  euler_tour.pb(u);
  for(auto v:g[u]){
    if(v==par)continue;
    dfs(v,u);
  }
  op[u]=++tim;
  euler_tour.pb(u);
}
//another variant leaf only once used in lca 
void dfs(int node,int par=-1){
  in[node]=++tim;
  euler_tour.pb(node);
  for(auto nbr:graph[node]){
    if(nbr==par)continue;
    dfs(nbr,node);
    euler_tour.pb(node);
  }
  op[node]=++tim;
}

//bipartite check
void bipartite(int n){
  //nodes taken in 1-based indexing
  std::vector<int> side(n+1,-1);
  bool is_bipartite=true;
  std::vector<int>cnt[2];
  queue<int>q;
  for(int st=1;st<=n;st++){
    if(side[st]==-1 && graph[st].size()){
      q.push(st);
      side[st]=0;
      cnt[0].pb(st);
      while(!q.empty()){
        int node=q.front();
        q.pop();
        for(int nbr:graph[node]){
          if(side[nbr]==-1){
            side[nbr]=side[node]^1;
            cnt[side[nbr]].pb(nbr);
            q.push(nbr);
          }else{
            is_bipartite&=(side[nbr]!=side[node]);
          }
        }
      }
    }
  }
  if(!is_bipartite){
    out(-1);
  }else{
    for(auto el:cnt){
      out(el.size());
      for(auto &it:el){
        cout<<it<<" ";
      }
      out("");
    }
  }
}
//Finding Bridges 
std::vector<int> graph[N];
int n;
std::vector<bool> vis;
std::vector<int>tin,low;
int timer;
void IS_BRIDGE(int node,int nbr){
  //
}

void dfs(int node,int par=-1){
  vis[node]=true;
  tin[node]=low[node]=timer++;
  for(auto nbr:graph[node]){
    if(nbr==par){
      low[node]=min(low[node],tin[nbr]);
    }else{
      dfs(nbr,node);
      low[node]=min(low[node],low[nbr]);
      if(low[nbr]>tin[node]){
        IS_BRIDGE(node,nbr);
      }
    }
  }
}
void find_bridges(){
  timer=0;
  vis.assign(n+1,false);
  tin.assign(n+1,-1);
  low.assign(n+1,-1);
  //taking nodes as they are 1 based indexing
  for(int i=1;i<=n;++i){
    if(!vis[i]){
      dfs(i);
    }
  }
}

//finding articulation points
std::vector<int> graph[N];
int n;
std::vector<int> tin,low;
std::vector<bool> vis;
int timer;
unordered_set<int>s;
void IS_CUTPOINT(int node){
  s.insert(node);
}

void dfs(int node,int par=-1){
  vis[node]=true;
  low[node]=tin[node]=timer++;
  int children=0;
  for(auto nbr:graph[node]){
    if(nbr==par)continue;
    if(vis[nbr]){
      low[node]=min(low[node],tin[nbr]);
    }else{
      dfs(nbr,node);
      low[node]=min(low[node],low[nbr]);
      if(low[nbr]>=tin[node] && par!=-1){
        IS_CUTPOINT(node);
      }
      ++children;
    }
  }
  if(par==-1 and children>1){
    IS_CUTPOINT(node);
  }
}
void find_articulation_points(){
  timer=0;
  vis.assign(n+1,false);
  tin.assign(n+1,-1);
  low.assign(n+1,-1);
  s.clear();
  for(int i=1;i<=n;++i){
    if(!vis[i])
      dfs(i);
  }
}

//kosaraju's algorithm
std::vector<int> graph[N];
std::vector<bool> used;
std::vector<int> order,component;
int n;
void dfs1(int node){
  used[node]=true;
  for(auto nbr:graph[node]){
    if(!used[nbr])
      dfs1(nbr);
  }
  order.pb(node);
}
void dfs2(int node){
  used[node]=true;
  component.pb(node);
  for(auto nbr:graph[node])
    if(!used[nbr])
      dfs2(nbr);
}
void get_component(){
  //

}
void kosaraju(){
  used.assign(n+1,false);
  for(int i=1;i<=n;++i){
    if(!used[i])
      dfs1(i);
  }
  used.assign(n+1,false);
  for(int i=1;i<=n;++i){
    int node=order[n-i];
    if(!used[node]){
      dfs2(node);
      get_component();
      component.clear();
    }
  }
}

