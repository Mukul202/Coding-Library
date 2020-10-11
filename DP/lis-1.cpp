int lis(std::vector<int> v) {
    if(v.size()==0){
      return 0;
    }
    int ans = 0;
    std::vector<int> dp(v.size(), 1);
    //dp[i] indicates the length of max lis ending at v[i]
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (v[j] < v[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    return ans = *max_element(all(dp));
}
