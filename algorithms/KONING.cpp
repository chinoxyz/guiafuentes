
bool solx[M];
bool soly[M];
bool visit[M];

int BFS(int first){
  visit[first] = true;
  int actual, next;
  queue<int> cola;
  cola.push(first);
  
  while(!cola.empty()){
    actual = cola.front();
    cola.pop();
    visit[actual] = true;
    for(int i = 0; i < salida[actual].size(); i++){
      next = salida[actual][i];
      if(visit[next] || next == sumidero) continue;
      if(actual < q && orden[actual] != next){
        cola.push(next);
      }
      if(actual >= q && ordeninv[actual] == next){
        cola.push(next);
      }
    }
  }
}

int result(){
  for(int i = 0; i < M; i++){
    solx[i] = false;
    soly[i] = false;
  }
  int num = max_flow(r);
  memset(visit, 0, sizeof(visit));
  for(int i = 0; i < r; i++){
    if(salida[i].size() > 0 && orden[i] < 0){
      BFS(i);
    }
  }
  for(int i = 0; i < r; i++){
    if(salida[i].size() > 0 && !visit[i]) soly[i] = true;
  }
  for(int i = 0; i < c; i++){
    if(salida[i+q].size() > 0 && visit[i+q]) solx[i] = true;
  }
  return num;
}
