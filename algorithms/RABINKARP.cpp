#define B 261
const int L = 2000000;
unsigned long long H[L],powB[L];

string sw; // Sum of strings.
unsigned long long get_hash(int l, int r){
    return H[r + 1] - H[l] * powB[r - l + 1];
}  
void init(){
  powB[0] = 1;    
  for(int i = 1;i < L;++i){
    powB[i] = powB[i - 1] * B;
  }
  H[0] = 0;
  for(int i = 0;i < sw.size();++i){
    H[i + 1] = sw[i] + H[i] * B;
  }
}
// px, py pointers, lx, ly lengths
bool check(int px, int lx, int py, int ly){
    unsigned long long hx = get_hash(px,px + lx - 1);
    for(int i = 0;i + lx <= ly;++i)
        if(get_hash(py + i,py + i + lx - 1) == hx)
            return true;    
    return false;
}
