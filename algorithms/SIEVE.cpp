#define SIZE 10009
int sieve[SIZE], primes[SIZE], prime_size;
vector<int> primos;
void initsieve(){
  int a, b;
  prime_size = 0;
  memset(sieve, 0, sizeof(sieve));
  sieve[0] = sieve[1] = 1;
  for(a = 2 ; a < SIZE ; a++){
    if(!sieve[a]){
      primos.push_back(a);
      primes[prime_size++] = a;
      for (b = a+a ; b < SIZE ; b += a){
        sieve[b] = 1;
      }
    }
  }
}