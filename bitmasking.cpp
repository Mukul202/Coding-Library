void clearBit(int &n, int i) {
    int mask = ~(1LL << i);
    n = n & mask;
}
void updateBit(int &n, int i, int v) {
    //update ith bit of n with ith bit of v
    int mask = ~(1LL << i);
    int cleared_n = n & mask;
    n = cleared_n | (v << i);
}

int decimaltoBinary(int &n) {
    int ans = 0, p = 1;
    //1101->13 remove bits one by one
    while (n > 0) {
        int last_bit = (n & 1LL);
        ans += mult(p, last_bit);
        n = (n >> 1LL);
        p *= 10;
    }
    return ans;
}

int get_ith_bit(int n,int i){
    int mask=(1LL<<i);
    return (n&mask);
}

int LSB(int x){
    return x&-x;
}
int unsetLsb(int x){
    return x&(x-1);
}
int set_last_unset_bit(int x){
    return x|(x+1);//used in BIT
}
//setting trailing zeroes to 1 and LSB to 0
int set_unset_and_unset_LSB(int x){
    return x-1;
}
int unset_set_and_set_first_zero(int x){
    return x+1;   
}

//generating all submasks of a subset
void gen_submask(int subset){
    //O(3^n) if enumerating for every subset
    //it generates submasks in descending order
    for(int mask=subset;mask!=0;mask=(mask-1)&subset){
        //code
    }
}