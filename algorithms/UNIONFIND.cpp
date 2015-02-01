#define MAX 10005
int uf[MAX];
int FIND(int x){ return uf[x]==x? x:uf[x] = FIND(uf[x]); }
void UNION(int x,int y){ uf[FIND(x)] = FIND(y); }
void init(int n){
  for(int i = 0; i < n; i++){
    uf[i] = i;
  }
}
