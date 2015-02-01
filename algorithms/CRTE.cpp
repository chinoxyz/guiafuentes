bool CRT(long long a1, long long n1, long long a2, long long n2, long long &a0, long long &n0){
  long long gcdn1n2 = gcd(n1, n2);
  long long lcmn1n2 = n1*n2/gcdn1n2;
  if(a1 % gcdn1n2 != a2 % gcdn1n2) return false;
  long long x, y;
  extended_gcd(n1, n2, x, y);
  long long q1, q2, r;
  r = a1 %  gcdn1n2;
  q1 = a1 / gcdn1n2;
  q2 = a2 / gcdn1n2;
  long long res = q2*x*n1 + q1*y*n2 + r;
  res = ((res % lcmn1n2) + lcmn1n2)%lcmn1n2;
  a0 = res;
  n0 = lcmn1n2;
  return true;
}
