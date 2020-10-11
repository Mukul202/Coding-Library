struct fenwick
{
    std::vector<int> f;
    int n;
    void init(int n) {
        this->n = n;
        f.resize(n, 0);
    }
    void update(int x, int val) {
        x++;
        while (x < n) {
            f[x] = max(f[x], val);
            x += (x & -x);
        }
    }
    int query(int x) {
        x++;
        int res = 0;
        while (x) {
            res = max(res, f[x]);
            x -= (x & -x);
        }
        return res;
    }
};
int dx[8] = {0, -1, 0, 1, -1, -1, 1, 1} ;
int dy[8] = { -1, 0, 1, 0, -1, 1, 1, -1} ;
inline void solve() {
    int n;
    cin >> n;
    pii a[n];
    fr(i, n) {
        cin >> a[i].ff;
        a[i].ss = i;
    }
    sort(a, a + n);
    fenwick tree;
    tree.init(n);
    int dp[n];
    fr(i, n) {
        int val = a[i].ff;
        int ind = a[i].ss;
        dp[ind] = tree.query(ind - 1) + 1;
        tree.update(ind, dp[ind]);
    }
    for (auto el : dp) {
        cout << el << " ";
    }
    out("");
    out(*max_element(dp, dp + n));
}
