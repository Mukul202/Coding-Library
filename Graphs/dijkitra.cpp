template<typename T>
class graph
{
    unordered_map<T, list<pair<T, int>>>m;
    int V;
public:
    graph(int n) {
        this->V = n;
    }
    void addedge(T u, T v, int dis, bool bidir = true) {
        m[u].pb({v, dis});
        if (bidir) {
            m[v].pb({u, dis});
        }
    }
    void dijkitra(T src) {
        map<T, int>dis;
        for (auto j : m) {
            dis[j.first] = INT_MAX;
        }
        set<pair<int, T>>s;
        dis[src] = 0;
        s.insert(mp(0, src));
        while (!s.empty()) {
            auto p = *(s.begin());
            T node = p.second;
            int nodedis = p.first;
            s.erase(s.begin());
            //iterate over neighbour of current node
            for (auto childpair : m[node]) {
                if (nodedis + childpair.second < dis[childpair.first]) {
                    T dest = childpair.first;
                    auto f = s.find(mp(dis[dest], dest));
                    if (f != s.end()) {
                        s.erase(f);
                    }
                    dis[dest] = nodedis + childpair.second;
                    s.insert(mp(dis[dest], dest));
                }
            }
        }
        for (auto j = 1; j <= V; j++) {
            if (j != src) {
                if (dis[j] == INT_MAX) {
                    cout << -1 << " ";
                }
                else if (dis[j] == 0) {
                    //not present
                    cout << -1 << " ";
                }
                else {
                    cout << dis[j] << " ";
                }
            }
        }
        cout<<"\n";
    }
};
