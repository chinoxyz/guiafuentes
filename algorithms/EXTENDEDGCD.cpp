long long extended_gcd(long long a, long long b){ //, long long &r1, long long &r2
  long long x = 0, lastx = 1;
  long long y = 1, lasty = 0;
  while (b != 0){
    long long quotient = a / b;
    c(b, a % b, a, b);
    c(lastx - quotient*x, x, x, lastx);
    c(lasty - quotient*y, y, y, lasty);
  }
  // r1 = lastx; r2 = lasty;
  return lastx;
}
