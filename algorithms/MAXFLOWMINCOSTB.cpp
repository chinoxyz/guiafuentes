/*
 * MAX FLOW MIN COST WITH BELLMAN FORD
 */
struct MinCostMaxFlow {
  int n;

  lint cap[mn][mn];
  lint cost[mn][mn];
  lint d[mn];
  lint p[mn];
  
  MinCostMaxFlow(int nn){
    n = nn;
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        cap[i][j] = 0;
        cost[i][j] = 0;
      }
    }
  }
  
  void AddEdge(int from, int to, lint cap, lint cost) {
    this->cap[from][to] = cap;
    this->cap[to][from] = 0;
    this->cost[from][to] = cost;
    this->cost[to][from] = -cost;
  }
  
  lint bellman(int s, int t){
    for(int i = 0; i < n; i++){
      d[i] = linf;
      p[i] = -1;
    }
    d[s] = 0;
    p[s] = -1;
    for(int i = 0; i < n; i++){
      for(int u = 0; u < n; u++){
        for(int v = 0; v < n; v++){
          if(cap[u][v] > 0 && d[v] > d[u] + cost[u][v]){
            d[v] = d[u]+cost[u][v];
            p[v] = u;
          }
        }
      }
    }
    
    return d[t];
  }
  
  lint GetMaxFlow(int so, int si, int k){
    lint rp ,res;
    res = 0;
    
    for(int i = 0; i < k; i++){
      rp = bellman(so,si);
      vector<int> ve;
      int u = si, v;
      while(u != -1){
        ve.pb(u);
        u = p[u];
      }
      if(rp >= linf) return res;
      
      for(int i = 1; i < ve.size(); i++){
        v = ve[i-1];
        u = ve[i];
        cap[u][v]--;
        cap[v][u]++;
      }
      res+= rp;
    }
    return res;
  }
  
  
};
