/**
 * Tarjan's algorithm for finding biconnected componets in UNDIRECTED GRAPHS.
 * 
 * Finds all bridges (isthmus, cut-edges), articulation points (cut-vertex),
 * and biconnected components in a provided undirected graph.
 *
 * @param MAXN          The maximum number of nodes in the graph.
 * @param graph         Adjecency-list description of the graph.
 * @param n             Number of nodes in the graph.
 * @return bridges      All bridges in the graph.
 * @return b_comp       All biconnected components in the graph, the
 *                      components are given as a set of non-repeated
 *                      edges. The direction of the edges follow
 *                      a DFS in the biconneced component.
 * @return a_points     All articulation points in the provided graph.
 *
 * @time: O(|E|+|V|)
 * @test: (uva)796, 610, 315
 */

//........Params begin..................
#define MAXN 10000
vector< vector<int> > graph;
int n;
//........Params end..................

vector< vector< pair<int,int> > > b_comp;
vector< pair<int,int> > bridges;
vector< int > a_points;
stack< pair<int,int> > stk;
int depth[MAXN], low[MAXN];

inline void new_b_comp(int v, int w){
    int x = b_comp.size();
    b_comp.push_back(vector< pair<int,int> >());
    bool stop = false;
    while(!stop){
        b_comp[x].push_back(stk.top());
        stop = stk.top().first == v && stk.top().second == w;
        stk.pop();
    }
}

void b_comp_dfs(int p, int v){
    low[v] = depth[v];
    bool is_a_point = false;
    for(int i=0;i<graph[v].size();i++){
        int w = graph[v][i];
        if(w==p || depth[w] > depth[v]) continue;
        stk.push(make_pair(v,w));
        if(depth[w]==-1){
            depth[w] = depth[v]+1;
            b_comp_dfs(v,w);
            low[v] = min(low[v],low[w]);
            if(low[w] >= depth[v]) //v is an articulation point
                is_a_point = true, new_b_comp(v,w);
            if(low[w]==depth[w]) //v - w is a bridge
                bridges.push_back(make_pair(min(v,w),max(v,w)));
        }
        else low[v] = min(low[v],depth[w]);
    }
    //root-nodes need a diffetent analysis
    if(depth[v]!=0 && is_a_point) a_points.push_back(v);
}

//Main function. The for cycle can be erased if it is
//warrantied that the graph is connected.
inline void find_b_comp(){
    b_comp.clear(), bridges.clear(), a_points.clear();
    memset(depth,-1,sizeof(int)*n);
    stk = stack< pair<int,int> >();
    for(int i=0;i<n;i++) if(depth[i]==-1) {
        depth[i] = 0, b_comp_dfs(-1,i);
        //Analyze if i is an a_point
        int count = 0;
        for(int j=0;j<graph[i].size() && count<2;j++)
            if(depth[graph[i][j]]==1) count++;
        if(count > 1) a_points.push_back(i);
    }
}
