#define MAXN 100000
#define T int
#define neutro 0//Neutro es el neutro de la funcion del segment tree
//El indice 0 se desperdicia, se guardan los datos desde el indice 1
T input[MAXN];
//El tamano del arbol debe ser N*logN, en este caso el log 100000 es 17 aprox
T tree[MAXN*17];

//Esta es la funcion que define lo que guarda el segment tree
//En este caso es suma pero puede ser maximo o minimo
T f(T a, T b) {
    return a + b;
}

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
T query(int node, int b, int e, int i, int j) {
	if(i > e || j < b) return neutro;
	if (i <= b && e <= j) return tree[node];
	else {
		int m = (b + e) >> 1, lt = node << 1, rt = lt | 1;
		return f(query(lt, b, m, i, j), query(rt, m+1, e, i, j));
	}
}

void modify(int node, int b, int e, int i, int v) {
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
