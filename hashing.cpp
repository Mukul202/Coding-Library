#include <bits/stdc++.h>
using namespace std;
#define FILE                          \
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout)
#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);


//better than unordered_map
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, int> table;

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<key, int, chash> table;


//use this cc_hash_table better than unordered_map and gp_hash_table
//and don't use custom_hash

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef cc_hash_table<int, int, hash<int>> ht;


struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

//function to remove duplicate elements
std::vector<int> get_unique(std::vector<int>&v){
	sort(all(v));
	auto p=unique(all(v),[](int a,int b){
		return a==b;
	});
	v.resize(distance(v.begin(),p));
	return v;
}

vector<vector<int>> merge(vector<vector<int>>& intervals) {
  int n=intervals.size();
  if(n==0){
    return {};
  }
  vector<vector<int>>ans;
  sort(intervals.begin(),intervals.end());
  auto already=intervals[0];
  for(int i=0;i<n;i++){
    if(intervals[i][0]<=already[1]){
                //it merges
      already[0]=min(already[0],intervals[i][0]);
      already[1]=max(already[1],intervals[i][1]);
    }
    else{
      ans.push_back(already);
      already=intervals[i];
    }
  }
  ans.push_back(already);
  return ans;
}

void solve(){
	int n;
	cin>>n;
	cout<<n;
}
int main()
{
	fio;
#ifndef ONLINE_JUDGE
  FILE;
#endif
  solve();
	return 0;
}