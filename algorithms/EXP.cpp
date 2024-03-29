// sum a**i = (a**(n+1) -1) / (a-1)
long long exp(long long a, long long b, long long m){
  long long result = 1;
  long long power = a;
  while(b>0) {
    if (b%2==1) result = (result*power)%m;
    power = (power*power)%m;
    b = b/2;
  }
  return result;
}
