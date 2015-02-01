#define MAXN 5009
#define MAXM 60009
#define INF 1000000009
#define lint long long
class Dinic {
	int n, m, head[MAXN], level[MAXN], s, t, work[MAXN];
	struct edge {
		int v, c, f, nxt;
		edge() {}
		edge(int v, int c, int f, int nxt): v(v), c(c), f(f), nxt(nxt) {}
	} e[MAXM];
	bool _bfs() {
		static int q[MAXN];
		memset(level, -1, sizeof(int) * n);
		int le = 0, ri = 0;
		q[ri++] = s;
		level[s] = 0;
		while(le < ri) {
			for(int k = q[le++], i = head[k]; i != -1; i = e[i].nxt) {
				if(e[i].f < e[i].c && level[e[i].v] == -1) {
					level[e[i].v] = level[k] + 1;
					q[ri++] = e[i].v;
				}
			}
		}
		return (level[t] != -1);
	}
	int _dfs(int u, int f) {
		if(u == t)
			return f;
		for(int& i = work[u]; i != -1; i = e[i].nxt) {
			if(e[i].f < e[i].c && level[u] + 1 == level[e[i].v]) {
				int minf = _dfs(e[i].v, min(f, e[i].c - e[i].f));
				if(minf > 0) {
					e[i].f += minf;
					e[i ^ 1].f -= minf;
					return minf;
				}
			}
		}
		return 0;
	}
public:
	void init(int nn, int src, int dst) {
		n = nn;
		s = src;
		t = dst;
		m = 0;
		memset(head, -1, sizeof(int) * n);
	}
	void addEdge(int u, int v, int c, int rc) {
		assert(u < n);
		assert(v < n);
		e[m] = edge(v, c, 0, head[u]);
		head[u] = m++;
		e[m] = edge(u, rc, 0, head[v]);
		head[v] = m++;
		assert(m < MAXM);
	}
	lint maxFlow() {
		lint ret = 0;
		while(_bfs()) {
			memcpy(work, head, sizeof(int) * n);
			while(true) {
				int delta = _dfs(s, INF);
				if(delta == 0)
					break;
				ret = ret + delta;
			}
		}
		return ret;
	}
};

Dinic d;

int dinic(){
  
  d.init(n+1, source, sink);
  while( m-- ){
      int u, v, c; scanf("%d %d %d", &u, &v, &c );
      u;
      v;
      d.addEdge(u,v,c,c);
  }
  return d.maxFlow();
}
