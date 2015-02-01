
const int mn = 20009; // MAX NUMBER OF NODES
const int lmn = 30; // LG MAX NUMBER OF NODES

/* RANGE TREE INIT */

// TYPE RANGE TREE
struct tt{
  int a;
  tt(int aa = 0){ a = aa; }
  static int neutro(){
    return -inf;
  }
};
tt f(tt a, tt b){
  return tt(max(a.a, b.a));
}
// (USE CID[i] as index for every node in the range tree)
tt input[mn]; // RANGE TREE INIT VALUES 
tt tree[mn*lmn]; // RANGE TREE VALUES
// init(1,1,n)
void init(int node, int b, int e) {
	if(b == e) tree[node] = input[b];
	else {
		int m = (b + e) >> 1, lt = node << 1, rt = lt | 1;
		init(lt, b, m);
		init(rt, m+1, e);
		tree[node] = f(tree[lt], tree[rt]);
	}
}
// query(1,1,N,i,j)
tt query(int node, int b, int e, int i, int j) {
	if(i > e || j < b) return tt::neutro();
	if (i <= b && e <= j) return tree[node];
	else {
		int m = (b + e) >> 1, lt = node << 1, rt = lt | 1;
		return f(query(lt, b, m, i, j), query(rt, m+1, e, i, j));
	}
}
// modify (1,1,n, i, v);
void modify(int node, int b, int e, int i, tt v) {
  if(i > e || i < b) return;
  if (i <= b && e <= i) {
    tree[node] = v;
    return;
  }
  int m = (b + e) >> 1, lt = node << 1, rt = lt | 1;
  modify(lt, b, m, i, v);
  modify(rt, m+1, e, i, v);
  tree[node] = f(tree[lt], tree[rt]);
}

/* RANGE TREE END */


int n; // Nodes in graph
vector<int> g[mn]; // Graph (TREE)

/* HEAVY LIGHT INIT */
int S[mn]; // Subtree node sum;
int L[mn]; // L is the level of the node
int T[mn]; // Father of node
int H[mn]; // Head of the chain
int CID[mn]; // Chain ID
int CIDI[mn]; // Chain ID Inverse
int nid; // CID counter

int dfs(int u, int w){
  T[u] = w;
  int v;
  int sum = 1;
  for(int i = 0; i < g[u].size(); i++){
    v = g[u][i];
    if(v == w) continue;
    L[v] = L[u]+1; 
    sum = sum+dfs(v,u);
  }
  return S[u] = sum;
}

void dfs2(int u, int w){
  CIDI[nid] = u;
  CID[u] = nid++;
  vector<pii> ve;
  
  int v;
  for(int i = 0; i < g[u].size(); i++){
    v = g[u][i];
    if(v == w) continue;
    ve.pb(mp(S[v],v));
  }
  if(ve.empty()) return;
  sort(ve.begin(), ve.end());
  reverse(ve.begin(), ve.end());
  
  for(int i = 0; i < ve.size(); i++){
    v = ve[i].Y;
    if(i == 0){
      H[v] = H[u];
    }else{
      H[v] = v; 
    }
    dfs2(v, u);
  }
}

// INIT OF HEAVY LIGHT
int init(){
  int init = 0;
  L[init] = 0;
  dfs(init,-1);
  nid = 1;
  H[init] = init;
  dfs2(init,-1);
}
/* HEAVY LIGHT END */


// LCA heavy light 
int LCA(int p, int q){
  while(H[p] != H[q]){
    if(L[H[p]] < L[H[q]]){
      swap(p,q);
    } 
    if(p == H[p]){
      p = T[p]; 
    }else{
      p = H[p];
    }
  }
  
  if(L[p] > L[q]) return q;
  return p;
}

// HL Query on path p to LCA
tt query(int p, int lca){
  tt res = tt::neutro();
  
  while(H[p] != H[lca]){
    res = f(res, query(1,1,n, CID[H[p]], CID[p]));
    p = T[H[p]];
  }
  return f(res, query(1,1,n, CID[lca], CID[p]));
}

// HL Modify node p with value v
void modify(int p, tt v){
  modify(1,1,n, CID[p], v);
}

