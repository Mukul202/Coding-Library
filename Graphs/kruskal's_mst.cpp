class dsu
{
    int* parent;
    int* rank;
public:
    dsu(int n) {
        parent = new int[n];
        rank = new int[n];
        fr(i, n) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }
    int get(int i) {
        return (parent[i] == -1 ? i : (parent[i] = get(parent[i])));
    }
    void unite(int x, int y) {
        int s1 = get(x);
        int s2 = get(y);
        if (s1 != s2) {
            if (rank[s1] >= rank[s2]) {
                rank[s1] += rank[s2];
                parent[s2] = s1;
            }
            else {
                rank[s2] += rank[s1];
                parent[s1] = s2;
            }
        }
    }
};
struct edge
{
    int w;
    int x;
    int y;
};
class graph
{
    std::vector<edge> edgelist;
    int V;
public:
    graph(int V) {
        this->V = V;
    }
    void addedge(int x, int y, int w) {
        edgelist.pb((edge) {w, x, y});
    }
    int kruskal_mst() {
        //main logic of kruskal's algorithm
        //first step to sort all the edges based on weights
        sort(all(edgelist), [](edge a, edge b) {
            return a.w < b.w;
        });
        dsu s(V);
        int ans = 0;
        for (auto edg : edgelist) {
            int w = edg.w;
            int x = edg.x;
            int y = edg.y;
            //check if it doesnt form a cycle
            if (s.get(x) != s.get(y)) {
                s.unite(x, y);
                ans += w;
            }
        }
        return ans;
    }
};
inline void solve() {
    int n, m;
    cin >> n >> m;
    graph g(n);
    while (m--) {
        int x, y, w;
        cin >> x >> y >> w;
        x--;
        y--;
        g.addedge(x, y, w);
    }
    out(g.kruskal_mst());
}
