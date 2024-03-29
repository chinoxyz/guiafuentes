#define M 10009
#define LM 100
#define lint long long
int t, n;
char s[100];

vector<pair<int,int> > salida[M];
int L[M]; // L is the level of the node
int T[M]; // Father of node
lint C[M]; // Cost to father
lint PATH[M]; // Cost to root
int P[M][LM]; // DP path 2**i

int bfs(int ini){
  int u, v;
  pair<int,int> p1,p2;
  queue< pair<int, int> > Q;
  Q.push(make_pair(ini,0));
  
  for(int i = 0; i < n; i++){
    T[i] = -1;
    PATH[i] = 0;
  }
  
  while(!Q.empty()){
    p1 = Q.front();
    Q.pop();
    
    u = p1.second;
    
    L[u] = p1.first;
    
    for(int i = 0; i < salida[u].size(); i++){
      v = salida[u][i].second;
      if(T[v] == -1 && v != ini){
        T[v] = u;
        C[v] = salida[u][i].first;
        PATH[v] = PATH[u] + C[v];
        p2.first = p1.first+1;
        p2.second = v;
        Q.push(p2);
      }
    }
  }
}

void process3(int N){
  int i, j;
  //we initialize every element in P with -1
  for(i = 0; i < N; i++){
    for(j = 0; 1 << j < N; j++){
      P[i][j] = -1;
    }
  }
  //the first ancestor of every node i is T[i]
  for (i = 0; i < N; i++){
    P[i][0] = T[i];
  }
  //bottom up dynamic programing
  for(j = 1; 1 << j < N; j++){
    for(i = 0; i < N; i++){
      if(P[i][j - 1] != -1){
        P[i][j] = P[P[i][j - 1]][j - 1];
      }
    }
  }
}

int LCA(int N, int p, int q){
  int tmp, log, i;
  //if p is situated on a higher level than q then we swap them
  if(L[p] < L[q]){
    tmp = p, p = q, q = tmp;
  }
  //we compute the value of [log(L[p)]
  for(log = 1; 1 << log <= L[p]; log++);
  log--;
  //we find the ancestor of node p situated on the same level
  //with q using the values in P
  for (i = log; i >= 0; i--){
    if (L[p] - (1 << i) >= L[q]){
      p = P[p][i];
    }
  }
  if(p == q){
    return p;
  }
  //we compute LCA(p, q) using the values in P
  for (i = log; i >= 0; i--){
    if (P[p][i] != -1 && P[p][i] != P[q][i]){
      p = P[p][i], q = P[q][i];
    }
  }
  return T[p];
}

int init(){
  bfs(0);
  process3(n);
}
