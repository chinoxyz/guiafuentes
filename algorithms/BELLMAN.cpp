for v pertenece V[G] do
  distancia[v]=INFINITO
  predecesor[v]=NIL
distancia[s]=0
for i=0 to n-1 do
  for (u, v) pertenece E[G] do
    if distancia[v] > distancia[u] + peso(u, v) then
      distancia[v] = distancia[u] + peso (u, v)
      predecesor[v] = u
