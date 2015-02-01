#define MAXN 100000
#define T int
#define neutro 0
// entrada, arbol, acumulado(propagacion) elemento 0 se desperdicia
T input[MAXN]; T tree[MAXN*17]; T acum[MAXN*17]; 
T f(T a, T b) { return a + b; } // Funcion que mantiene el segment tree
// init(1,1,n)
void init(int node, int b, int e) {
  acum[node] = 0;
	if(b == e) tree[node] = input[b];
	else {
		int m = (b + e) >> 1, lt = node << 1, rt = lt | 1;
		init(lt, b, m);
		init(rt, m+1, e);
		tree[node] = f(tree[lt], tree[rt]);
	}
}
// query(1,1,N,i,j)
T query(int node, int b, int e, int i, int j) {
  int m = (b + e) >> 1, lt = node << 1, rt = lt | 1;
  
  tree[node] += acum[node] * (e - b + 1);
  acum[lt] += acum[node];
  acum[rt] += acum[node];
  acum[node] = 0;
  
	if(i > e || j < b) return neutro;
	if (i <= b && e <= j) return tree[node];
	else return f(query(lt, b, m, i, j), query(rt, m+1, e, i, j));
}
// modify(1,1,N,i,j,val)
void modify(int node, int b, int e, int i, int j, int v) {
  int m = (b + e) >> 1, lt = node << 1, rt = lt | 1;  
  tree[node] += acum[node] * (e - b + 1);
  acum[lt] += acum[node];
  acum[rt] += acum[node];
  acum[node] = 0;
  if(i > e || j < b) return;
	if (i <= b && e <= j) {
	  tree[node] += v * (e - b + 1);
	  acum[lt] += v;
    acum[rt] += v;
	  return;
	}
	modify(lt, b, m, i, j, v);
	modify(rt, m+1, e, i, j, v);
	tree[node] = f(tree[lt], tree[rt]);
}
