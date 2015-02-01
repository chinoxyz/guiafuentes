// LEAST ROTATION STRING
int len;
char S[200009]; // S+S // CONCATENATED
int f[200009];

int LCS(){
  int k, i, n = len;
  memset(f, -1, sizeof(f));
  k = 0;       //# Least rotation of string found so far
  for(int j = 1; j < 2*n; j++){
    i = f[j-k-1];
    while(i != -1 && S[j] != S[k+i+1]){
      if(S[j] < S[k+i+1]) k = j-i-1;
      i = f[i];
    }
    if(i == -1 && S[j] != S[k+i+1]){
      if(S[j] < S[k+i+1]) k = j;
      f[j-k] = -1;
    }else{
      f[j-k] = i+1;
    }
  }
  return (k);
}
