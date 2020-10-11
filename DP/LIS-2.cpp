int lis(std::vector<int> v) {
    if(v.size()==0){
      return 0;
    }
    std::vector<int> seq;
    seq.push_back(v[0]);
    for (int i = 1; i < v.size(); i++) {
        if (seq.back() < v[i]) {
            seq.push_back(v[i]);
        }
        else {
            int ind = lower_bound(all(seq), v[i]) - seq.begin();
            seq[ind] = v[i];
            deb(ind);
        }
    }
    return (seq.size());
}
