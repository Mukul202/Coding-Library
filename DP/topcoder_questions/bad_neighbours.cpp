inline int solve(std::vector<int> v) {
    int n = v.size();
    if (n < 2) {
        return n == 0 ? 0 : v[0];
    }
    std::vector<int> dp(n, 0), dp2(n, 0);
    std::vector<int> par(n, -1), par2(n, -1);
    int ans1, ans2;
    par[0] = 0;
    par[1] = 1;
    dp[0] = v[0];
    dp[1] = v[1];
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + v[i]);
        if (dp[i] == dp[i - 1]) {
            par[i] = par[i - 1];
        }
        else {
            par[i] = par[i - 2];
        }
    }
    if (par[n - 1] == 0) {
        ans1 = dp[n - 2];
    }
    else {
        return dp[n - 1];
    }
    par2[n - 1] = n - 1;
    par2[n - 2] = n - 2;
    dp2[n - 1] = v[n - 1];
    dp2[n - 2] = v[n - 2];
    for (int i = n - 3; i >= 0; i--) {
        dp2[i] = max(dp2[i + 1], dp2[i + 2] + v[i]);
        if (dp2[i] == dp2[i + 1])
            par2[i] = par2[i + 1];
        else
            par2[i] = par2[i + 2];
    }
    if (par2[0] == n - 1)
        ans2 = dp2[1];
    else
        return dp2[0];
    return max(ans1, ans2);
}
