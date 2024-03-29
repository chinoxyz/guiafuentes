#define MAXN 1000

//Tree has the BIT, n is the num of elements in the array
//and bitmask = 2^floor(lg2(n))
int tree[MAXN+1], n, bitmask;

//Returns the accumulated sum up to
//idx. However the first element of the array
//is 1 (not 0, careful witht that).
int read(int idx){
    int tot = 0;
    while(idx > 0){
        tot += tree[idx];
        idx ^= (idx&-idx);
    }
    return tot;
}

//Adds c to the array cell idx (1-indexed)
//and updates the structure
int update(int idx,int c){
    while(idx <= n){
        tree[idx] += c;
        idx += (idx&-idx);
    }
}

//Finds the right-most element which accumulated sum 
//is equal to s. The array is 1-indexed and
//only works if it does not have non-negative numbers.
int find(int s){
    int mask = bitmask, idx = 0;
    while(mask > 0){
        int tidx = idx+mask;
        if(tidx > n){mask>>=1;continue;}
        if(s >= tree[tidx]){
            s -= tree[tidx];
            idx = tidx;
        }
        mask >>= 1;
    }
    if(s!=0) return 0;
    return idx;
}
