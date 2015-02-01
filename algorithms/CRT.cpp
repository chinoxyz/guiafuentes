void c(long long a, long long b, long long &r1, long long &r2){
  r1 = a;
  r2 = b;
}

long long CRT(){
  for(int i = 0; i < n; i++){
    z[i] = m / b[i];
    y[i] = ((extended_gcd(z[i], b[i]) % b[i]) + b[i] )%b[i];
  }
  
  long long res = 0;
  for(int i = 0; i < n; i++){
    res = (res + (a[i]*y[i]*z[i]))%m;
  }
  
  res = (((res)%m) +m) %m;
  return res;
}
