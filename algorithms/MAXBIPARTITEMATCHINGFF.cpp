#define M 2009 
#define q 1002 
int r, c, n; 

int orden[M]; 
int sumidero = M-1; 
vector<int> salida[M]; 
int capacidad[M][M]; 
const int maxnodos = M; 

int from[M]; 
bool visitados[M]; 
int find_path(int source, int n) { 
  stack<int> Q; 
  bool terminar; 
  int where, next, prev, path_cap; 
  Q.push(source); 
  
  visitados[source] = true; 
  terminar = false; 
  while(!Q.empty() && !terminar){ 
    where = Q.top(); 
    Q.pop(); 
    for(int i = 0; i < salida[where].size(); i++){ 
      next = salida[where][i]; 
      if(!visitados[next] && capacidad[where][next] > 0){ 
        Q.push(next); 
        visitados[next]= true; 
        from[next] = where; 
        if(next == sumidero){ 
          terminar = true; 
          break; 
        } 
      } 
    } 
  } 
  where = sumidero; 
  
  if(terminar == false) return 0; 
  
  path_cap = 1; 
  
  where = sumidero; 
  while(from[where] > -1 && where != source){ 
    prev = from[where]; 
    if(prev < q){ 
      orden[prev] = where; 
    } 
    capacidad[prev][where] -= path_cap; 
    capacidad[where][prev] += path_cap; 
    where = prev; 
  } 
  return path_cap; 
} 

int max_flow(int n) { 
  int result, path_capacity; 
  result = 0; 
  
  for(int i = 0; i < n; i++){ 
    memset(from, -1, sizeof(from)); 
    memset(visitados, 0, sizeof(visitados)); 
    path_capacity = find_path(i, n); 
    result += path_capacity; 
  } 
  return result; 
}
