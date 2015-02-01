/**
 * Gabow's algorithm for finding a maximum match in a general (undirected) graph.
 *
 * Calculates a matching of the graphs in the array match[].
 * IMPORTANT: the provided graph must have three properties:
 * 1) The nodes are numbered from 1 to n. Node #0 is reserved for internal use.
 * 2) The provided graph must be an edge adjacency-list, which means that
 *      graph[v][i] must return the number of an edge. For knowing the nodes
 *      incident in an edge the array edge[][] is used.
 * 3) The edges are numbered from 0 to m-1.
 *
 * @param MAXN          The maximum number of nodes in the graph.
 * @param MAXM          The maximum number of edges in the graph.
 * @param graph         Edge adjecency-list description of the graph.
 * @param edge          Description of incident nodes in each edge. The edges
 *                      are numbered from 0 to m-1.
 * @param n             Number of nodes in the graph.
 * @param m             Number of edges in the graph.
 *
 * @return match        For every vertex i (between 1 and n), if i is a
 *                      matched vertex, then the edge (i,match[i]) is matched.
 *                      If i is not matched, then match[i] == 0.
 *
 * @time: O(|V|^3)
 * @test: (livearchive)4130, (timus)1099
 */

//........Params begin..................
#define MAXN 100
#define MAXM 100*100

vector< vector<int> > graph;
int edge[MAXM+1][2]; 
int n,m;
//........Params end..................

int match[MAXN+1]; 
int label[MAXN+1],first[MAXN+1];
queue<int> q;

void rematch(int v, int w){
    int t = match[v];
    match[v] = w;
    if(match[t] != v) return;
    if(label[v] <= n){
        match[t] = label[v];
        return rematch(label[v],t);
    }
    int e = label[v]-1-n,
        x = edge[e][0], y = edge[e][1];
    rematch(x,y);
    rematch(y,x);
}

inline void edge_label(int e){
    int x = edge[e][0], y = edge[e][1],
        r = first[x], s = first[y],
        flag = n+1+e, join;
    if(r==s) return;
    label[r] = label[s] = -flag;
    while(true){
        if(s!=0){int aux = s; s = r, r = aux;}
        r = first[label[match[r]]];
        if(label[r]==-flag){
            join = r;
            break;
        }
        label[r] = -flag;
    }
    for(int i=0;i<2;i++){
        int v = first[edge[e][i]];
        while(v!=join){
            label[v] = flag, first[v] = join;
            q.push(v);
            v = first[label[match[v]]];
        }
    }
    for(int i=1;i<=n;i++)
        if(label[i]>=0 && label[first[i]] >= 0)
            first[i] = join;
}

inline bool augpath(int u){
    memset(label,-1,sizeof(int)*(n+1));
    label[u] = first[u] = 0;
    q = queue<int>();
    q.push(u);
    while(!q.empty()){
        int x = q.front(); q.pop();
        for(int i=0;i<graph[x].size();i++){
            int e = graph[x][i],
                y = (edge[e][0] != x ? edge[e][0] : edge[e][1]);
            if(match[y] == 0 && y != u) {
                match[y] = x;
                rematch(x,y);
                return true;
            }
            if(label[y]>=0){
                edge_label(e);
                continue;
            }
            int v = match[y];
            if(label[v]<0){
                label[v] = x, first[v] = y;
                q.push(v);
            }
        }
    }
    return false;
}

//Main function, returns the number of matched edges found
inline int gabow(){
    memset(match,0,sizeof(int)*(n+1));
    int tot = 0;
    for(int i=1;i<=n;i++) {
        if(match[i]!=0) continue;
        if(augpath(i)) tot++;
    }
    return tot;
}
