// KMP
std::vector<int>prefix_function(string const& s) {
  int n = (int)s.size();
  std::vector<int> pref(n);
  pref[0] = 0;
  for (int i = 1; i < n; ++i) {
    int j = pref[i - 1];
    while (j > 0 and s[j] != s[i]) {
      j = pref[j - 1];
    }
    if (s[j] == s[i]) {
      j++;
    }
    pref[i] = j;
  }
  return pref;
}
bool is_substring(string const&s, string const&t) {
  string new_string = s + '#' + t;
  auto pref = prefix_function(new_string);
  int n = (int)s.size();
  std::vector<int> ans;//stores the indices of pat
  for (int i = n; i < (int)pref.size(); ++i) {
    if (pref[i] == n) {
      ans.pb(i - 2 * n);
    }
  }
  if (ans.size() == 0)
    cout << "Not Found";
  for (auto el : ans) {
    cout << el + 1 << " ";
  }
  return true;
}


//rabin karp
vector<int> rabin_karp(string const& s, string const& t) {
  const int p = 31;
  const int m = 1e9 + 7;
  int S = s.size(), T = t.size();

  vector<long long> p_pow(max(S, T));
  p_pow[0] = 1;
  for (int i = 1; i < (int)p_pow.size(); i++)
    p_pow[i] = (p_pow[i - 1] * p) % m;

  vector<long long> h(T + 1, 0);
  for (int i = 0; i < T; i++)
    h[i + 1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m;
  long long h_s = 0;
  for (int i = 0; i < S; i++)
    h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m;

  vector<int> occurences;
  for (int i = 0; i + S - 1 < T; i++) {
    long long cur_h = (h[i + S] + m - h[i]) % m;
    if (cur_h == h_s * p_pow[i] % m)
      occurences.push_back(i);
  }
  return occurences;
}


//Z function
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}