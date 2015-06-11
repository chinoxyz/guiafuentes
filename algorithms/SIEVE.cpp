#define SIZE 10009
bool sieve[SIZE];
vector<int> primos;
void initsieve(){
  int a, b;
  sieve[0] = sieve[1] = 1;
  for(a = 2 ; a < SIZE ; a++){
    if(!sieve[a]){
      primos.push_back(a);
      for (b = a+a ; b < SIZE ; b += a){
        sieve[b] = 1;
      }
    }
  }
}
