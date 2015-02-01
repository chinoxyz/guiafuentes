long long comb[2009][1009]; 
long long c = 1000000007; 

long long combdp(int n, int k){ 
  if(k == 0 || n == k) return 1; 
  if(comb[n][k] != -1) return comb[n][k]; 
  if(comb[n][n-k] != -1) return comb[n][n-k]; 
  if(k == 1 || n-1 == k) return n; 
  return comb[n][k] = ((combdp(n-1, k-1)%c + combdp(n-1, k)%c)%c+c) % c; 
}
