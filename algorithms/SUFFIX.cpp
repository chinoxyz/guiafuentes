/************************************************************************
 * Suffix Array builder.
 * @input
 *  s[MAXN] The string to process
 *  n       The size of the string, including the terminator!
 * 
 * @output
 *  sa[MAXN]  The suffix array
 *  lcp[MAXN] The LCP array.
 *
 * @time O(n*log(n))
 ************************************************************************/

#define MAXN 1000
#define ALPH_SIZE 256

int sa_[MAXN],*sa = &sa_[0], lcp[MAXN], n;
int sa2_[MAXN], grp_[MAXN], grp2_[MAXN], gs[MAXN], g,
    *sa2=&sa2_[0], *grp=&grp_[0], *grp2=&grp2_[0];

void suffix_array(char *s){
    memset(gs,0,sizeof(int)*ALPH_SIZE);
    for(int i=0;i<n;i++) gs[s[i]]++;
    for(int i=1;i<ALPH_SIZE;i++) gs[i] += gs[i-1];
    for(int i=n-1;i>=0;i--) sa[--gs[s[i]]] = i;

    grp[sa[0]] = gs[0] = g = 0;
    for(int i=1;i<n;i++){
        if(s[sa[i]] != s[sa[i-1]]) gs[++g] = i;
        grp[sa[i]] = g;
    }
    g++;
    for(int d=1;d<n&&g<n;d<<=1){
        for(int i=0;i<d;i++) sa2[gs[grp[n-i-1]]++] = n-i-1;
        for(int i=0;i<n;i++) if(sa[i]>=d) sa2[gs[grp[sa[i]-d]]++] = sa[i]-d;
        int *aux = sa; sa = sa2, sa2 = aux;
        
        grp2[sa[0]] = gs[0] = g = 0;
        for(int i=1;i<n;i++){
            if(grp[sa[i]] != grp[sa[i-1]] || sa[i]+d>=n || sa[i-1]+d>=n ||
               grp[sa[i]+d] != grp[sa[i-1]+d]) gs[++g] = i;
            grp2[sa[i]] = g;
        }
        g++;
        aux = grp; grp = grp2, grp2 = aux;
    }
    lcp[0] = 0;
    for(int i=0,l=0;i<n-1;i++,l--){
        if(l<0) l = 0;
        while(s[i+l] == s[sa[grp[i]-1]+l]) l++;
        lcp[grp[i]] = l;
    }
}

/************************************************************************
 * Suffix Tree builder.
 * @input
 *  sa[MAXN]  The suffix array
 *  lcp[MAXN] The LCP array.
 *  n         The size of the string
 *
 * @output
 *  sft   A pointer to the root of the suffix array
 *
 * @time O(n)
 ************************************************************************/

struct sufft {
  int b,l;
  sufft *f;
  vector<sufft*> *sons;
  
  sufft(){sons = new vector<sufft*>();f = NULL;}

  sufft(int b,int l, sufft *f){
    this->b = b;
    this->l = l;
    this->f = f;
    sons = new vector<sufft*>();
  }
};

sufft *sft;

void suffix_tree(){
  stack<int> st = stack<int>();
  sufft *root = new sufft(),
        *it = new sufft(sa[0],n-sa[0],root);
  root->b = root->l = 0; 
  root->sons->push_back(it);

  st.push(0);
  for(int i=1;i<n;i++){
    if(lcp[i] == lcp[st.top()]){
      int j = sa[i]+lcp[i];
      sufft *x = new sufft(j, n-j, it->f);
      it->f->sons->push_back(x);     
      it = x;
      st.push(i);
    }
    else if(lcp[i] > lcp[st.top()]){
      int ld = lcp[i] - lcp[st.top()],
          j = sa[i]+lcp[i];
      sufft *nit = new sufft(it->b+ld,it->l-ld,it),
            *x = new sufft(j, n-j, it);
      
      it->l = ld;
      vector<sufft*> *aux = nit->sons;
      nit->sons = it->sons;
      it->sons = aux;

      aux->push_back(nit); aux->push_back(x);

      it = x;
      st.push(i);
    }
    else {
      while(lcp[i] < lcp[st.top()]){
        int sz = it->f->sons->size();
        for(int j=0;j<sz-1;j++) st.pop();
        it = it->f;
      }
      i--;
    }
  }
  sft = root;
}

/************************************************************************
 * Suffix Array builder.
 * @input
 *  s[MAXN] The string to process
 *  n       The size of the string
 * 
 * @output
 *  sa[MAXN]  The suffix array
 *  lcp[MAXN] The LCP array.
 *
 * @time O(n)
 ************************************************************************/

inline bool leq(int a1, int a2,   int b1, int b2) {
  return(a1 < b1 || a1 == b1 && a2 <= b2); 
}                                              
inline bool leq(int a1, int a2, int a3,   int b1, int b2, int b3) {
  return(a1 < b1 || a1 == b1 && leq(a2,a3, b2,b3)); 
}
static void radixPass(int* a, int* b, int* r, int n, int K) 
{ 
  int* c = new int[K + 1];                    
  for (int i = 0;  i <= K;  i++) c[i] = 0;    
  for (int i = 0;  i < n;  i++) c[r[a[i]]]++; 
  for (int i = 0, sum = 0;  i <= K;  i++) { 
     int t = c[i];  c[i] = sum;  sum += t;
  }
  for (int i = 0;  i < n;  i++) b[c[r[a[i]]]++] = a[i]; 
  delete [] c;
}

void suffixArray(int *s, int* SA, int n, int K) {
  int n0=(n+2)/3, n1=(n+1)/3, n2=n/3, n02=n0+n2; 
  int* s12  = new int[n02 + 3];  s12[n02]= s12[n02+1]= s12[n02+2]=0; 
  int* SA12 = new int[n02 + 3]; SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
  int* s0   = new int[n0];
  int* SA0  = new int[n0];
 
  for (int i=0, j=0;  i < n+(n0-n1);  i++) if (i%3 != 0) s12[j++] = i;

  radixPass(s12 , SA12, s+2, n02, K);
  radixPass(SA12, s12 , s+1, n02, K);  
  radixPass(s12 , SA12, s  , n02, K);

  int name = 0, c0 = -1, c1 = -1, c2 = -1;
  for (int i = 0;  i < n02;  i++) {
    if (s[SA12[i]] != c0 || s[SA12[i]+1] != c1 || s[SA12[i]+2] != c2) { 
      name++;  c0 = s[SA12[i]];  c1 = s[SA12[i]+1];  c2 = s[SA12[i]+2];
    }
    if (SA12[i] % 3 == 1) { s12[SA12[i]/3]      = name; } 
    else                  { s12[SA12[i]/3 + n0] = name; }
  }

  if (name < n02) {
    suffixArray(s12, SA12, n02, name);
    for (int i = 0;  i < n02;  i++) s12[SA12[i]] = i + 1;
  } else 
    for (int i = 0;  i < n02;  i++) SA12[s12[i] - 1] = i; 

  for (int i=0, j=0;  i < n02;  i++) if (SA12[i] < n0) s0[j++] = 3*SA12[i];
  radixPass(s0, SA0, s, n0, K);

  for (int p=0,  t=n0-n1,  k=0;  k < n;  k++) {
#define GetI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
    int i = GetI(); 
    int j = SA0[p]; 
    if (SA12[t] < n0 ? 
        leq(s[i],       s12[SA12[t] + n0], s[j],       s12[j/3]) :
        leq(s[i],s[i+1],s12[SA12[t]-n0+1], s[j],s[j+1],s12[j/3+n0]))
    { 
      SA[k] = i;  t++;
      if (t == n02) { 
        for (k++;  p < n0;  p++, k++) SA[k] = SA0[p];
      }
    } else { 
      SA[k] = j;  p++; 
      if (p == n0)  { 
        for (k++;  t < n02;  t++, k++) SA[k] = GetI(); 
      }
    }  
  } 
  delete [] s12; delete [] SA12; delete [] SA0; delete [] s0; 
}

int s[MAXN], sa[MAXN], lcp[MAXN], n;
inline void suffix_array(int alph_size){
  s[n] = s[n+1] = s[n+2] = 0;
  suffixArray(s,sa,n,alph_size);

  int *pos = new int[n];
  for(int i=0;i<n;i++) pos[sa[i]] = i;

  for(int i=0,l=0;i<n;i++,l--){
    if(l<0) l = 0;
    int j = (pos[i] == 0 ? n : sa[pos[i]-1]);
    while(s[i+l] == s[j+l]) l++;
    lcp[pos[i]] = l;
  }
  lcp[0] = 0;

  delete [] pos;
}
