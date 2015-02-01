/**
 * Tarjan's algorithm for finding strongly connected components in DIRECTED GRAPHS.
 *
 * Calculates a partition of the graph's nodes in strongly connected components.
 *
 * @param MAXN          The maximum number of nodes in the graph.
 * @param graph         Adjecency-list description of the graph.
 * @param n             Number of nodes in the graph.
 * @return sc_comp_cnt  Contains the number of different strongly connected
 *                      components found.
 * @return sc_comp      Contains the str.conn.comp. to which it vertex belongs to,
 *                      i.e. sc_comp[i] = #of the str.conn.comp. of vertex i.
 *
 * @time: O(|E|+|V|)
 * @test: (spoj)BOTTOM
 */

//........Params begin..................
#define MAXN 5010

vector< vector<int> > graph;
int n;
//........Params end..................

int sc_comp[MAXN], sc_comp_cnt; 
int visit[MAXN], low[MAXN];
bool active[MAXN];
stack<int> stk;

inline void new_sc_comp(int v){
    bool stop = false;
    while(!stop){
        sc_comp[stk.top()] = sc_comp_cnt;
        active[stk.top()] = false;
        stop = stk.top() == v;
        stk.pop();
    }
    sc_comp_cnt++;
}

void scc_dfs(int v, int &step){
    low[v] = visit[v];
    active[v] = true, stk.push(v);
    for(int i=0;i<graph[v].size();i++){
        int w = graph[v][i];
        if(visit[w] == -1){
            visit[w] = step++;
            scc_dfs(w,step);
            low[v] = min(low[v],low[w]);
        }
        else if(active[w]) low[v] = min(low[v],visit[w]);
    }
    if(low[v]==visit[v]) new_sc_comp(v);
}

inline void find_sc_comps(){
    memset(visit,-1,sizeof(int)*n);
    //memset(active,false,sizeof(bool)*n);
    sc_comp_cnt = 0;
    stk = stack<int>();
    for(int i=0,step=0;i<n;i++) if(visit[i]==-1)
        visit[i] = step++, scc_dfs(i,step);
}
