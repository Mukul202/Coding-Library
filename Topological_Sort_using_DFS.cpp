template <typename T>
class graph
{
private:
    /* data */
    unordered_map<T, list<T>> l;

public:
    void addedge(T x, T y)
    {
        l[x].push_back(y);
    }
    void dfs_helper(T src, map<T, bool> &visited, list<T> &ordering)
    {
        visited[src] = true;
        for (auto nbr : l[src])
        {
            if (!visited[nbr])
            {
                dfs_helper(nbr, visited, ordering);
            }
        }
        ordering.push_front(src);
    }
    void dfs()
    {
        map<T, bool> visited;
        list<T> ordering;
        for (auto node_pair : l)
        {
            auto node = node_pair.ff;
            visited[node] = false;
        }
        for (auto nodes : l)
        {
            auto node = nodes.ff;
            if (!visited[node])
            {
                dfs_helper(node, visited, ordering);
            }
        }
        for (auto node : ordering)
        {
            out(node);
        }
    }
};
