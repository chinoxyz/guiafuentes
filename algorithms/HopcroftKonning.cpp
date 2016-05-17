// n: number of nodes on left side, nodes are numbered 1 to n
// m: number of nodes on right side, nodes are numbered n+1 to n+m
// G = NIL[0] U G1[G[1---n]] U G2[G[n+1---n+m]]
#include <bits/stdc++.h>
#define maxN 100001
#define NIL 0
#define INF (1<<28)

using namespace std;

bool mvc[maxN];
int n, m, match[maxN*2+5];
int dist[maxN];
vector<int> adj[maxN];
bool Free[maxN];
int arr[maxN];
bool bfs() {
    queue<int> Q;
    for (int i=1;i<=n;++i)
        if (!match[i]) {
            dist[i] = 0;
            Q.push(i);
        }
        else dist[i] = INF;
    dist[0] = INF;
    while (!Q.empty()) {
        int i = Q.front(); Q.pop();
        for (int k=0;k<adj[i].size();++k) {
            int j = adj[i][k];
            if (dist[match[j]] == INF) {
                dist[match[j]] = dist[i] + 1;
                Q.push(match[j]);
            }
        }
    }
    return dist[0] != INF;
}

bool dfs(int i) {
    if (!i) return true;
    for (int k=0;k<adj[i].size();++k) {
        int j = adj[i][k];
        if (dist[match[j]] == dist[i] + 1 && dfs(match[j])) {
            match[i] = j;
            match[j] = i;
            return true;
        }
    }
    dist[i] = INF;
    return false;
}

int hopcroft_karp() {
    int matching = 0;
    while (bfs())
        for (int i=1;i<=n;++i)
            if (!match[i] && dfs(i))
                matching++;
    return matching;
}


void dfs_konig(int i) {
    Free[i] = false;
    for (int k=0;k<adj[i].size();++k) {
        int j = adj[i][k];
        if (match[j] && match[j] != INF) {
            int x = match[j];
            match[j] = INF;
            if (Free[x]) dfs_konig(x);
        }
    }
}


void solve(){
	
	for (int i=1;i<=n;++i)
        if (!match[i])
            dfs_konig(i);
    for (int i=1;i<=n;++i)
        if (match[i] && Free[i])
            mvc[i]=true;
    for (int j=n+1;j<=n+m;++j)
        if (match[j] == INF)
            mvc[j]=true;
}

void init(){
	for (int i=1;i<=n+m;++i){
			Free[i]=true;
			adj[i].clear();
			match[i]=0;
			mvc[i]=false;
		}
}

