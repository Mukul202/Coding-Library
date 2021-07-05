struct LCA
{
	std::vector<int> height,euler,first,segtree;
	std::vector<bool> vis;
	int n;
	LCA(std::vector<std::vector<int>>&graph,int root=0){
		n=graph.size();
		height.resize(n);
		first.resize(n);
		euler.reserve(n*2);
		vis.assign(n,false);
		dfs(graph,root);
		int m=euler.size();
		segtree.resize(m*4);
		build(1,0,m-1);
	}
	void dfs(std::vector<std::vector<int>>&graph,int node,int h=0){
		vis[node]=true;
		height[node]=h;
		first[node]=euler.size();
		euler.push_back(node);
		for(auto nbr:graph[node]){
			if(!vis[nbr]){
				dfs(graph,nbr,h+1);
				euler.push_back(node);
			}
		}
	}
	void build(int node,int s,int e){
		if(s==e){
			segtree[node]=euler[s];
		}
		else{
			int mid=s+((e-s)>>1LL);
			build(node<<1LL,s,mid);
			build(node<<1LL|1LL,mid+1,e);
			int l=segtree[node<<1LL],r=segtree[node<<1LL|1];
			segtree[node]=(height[l]<height[r])?l:r;
		}
	}
	int query(int node,int s,int e,int l,int r){
		if(s>r || e<l){
			return -1;
		}
		if(s>=l and e<=r){
			return segtree[node];
		}
		int mid=s+((e-s)>>1LL);
		int left=query(node<<1LL,s,mid,l,r);
		int right=query(node<<1LL|1,mid+1,e,l,r);
		if(left==-1)return right;
		if(right==-1)return left;
		return (height[left]<height[right])?left:right;
	}
	int lca(int u,int v){
		int left=first[u],right=first[v];
		if(left>right)
			swap(left,right);
		return query(1,0,euler.size()-1,left,right);
	}
};

//RMQ by Cartesian Tree
void RMQ(std::vector<int>&a){
	int n=a.size();
	std::vector<int>par(n,-1);
	stack<int>s;
	for(int i=0;i<n;++i){
		int last=-1;
		while(!s.empty() and a[s.top()]>=a[i]){
			last=s.top();
			s.pop();
		}
		if(!s.empty())
			parent[i]=s.top();
		if(last>=0)
			parent[last]=i;
		s.push(i);
	}
}

//binary lifting
int n, l;
vector<vector<int>> adj;

int timer;
vector<int> tin, tout;
vector<vector<int>> up;

void dfs(int v, int p)
{
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];

    for (int u : graph[v]) {
        if (u != p)
            dfs(u, v);
    }

    tout[v] = ++timer;
}

bool is_ancestor(int u, int v)
{
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v)
{
    if (is_ancestor(u, v))
        return u;
    if (is_ancestor(v, u))
        return v;
    for (int i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v))
            u = up[u][i];
    }
    return up[u][0];
}

void preprocess(int root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(root, root);
}

//misc facts 
//dis(a,b)=depth[a]+depth[b]-2*depth[lca(a,b)]

//rerooting
void dfs(int node,int par){
	sz[node]=1;
	dp[node]=0;
	for(auto child:graph[node]){
		if(child!=par){
			dfs(child,node);
			sz[node]+=sz[child];
			dp[node]+=dp[child]+sz[child];
		}
	}
}

//general rerooting
void dfs2(int node,int par){
	int t1=dp[node];
	for(auto child:graph[node]){
		if(child!=par){
			int t2=dp[child];
			//transfer root from node to child

			dfs2(child,node);

			//rollback root to node
			//restore old values
			dp[node]=t1;
			dp[child]=t2;
		}
	}
}