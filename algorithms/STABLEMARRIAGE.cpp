
int gm[509][509]; //gm[i][j] mujer: que prefiere el hombre i en la posición j
int gw[509][509]; //gw[i][j] hombre: que prefiere la mujer i en la posición j

int pm[509][509]; //pm[i][j] posición, de la mujer j preferido por i
int pw[509][509]; //pw[i][j] posición, del hombre j preferido por i

int nm[509];

int engmw[509]; // engaged man to woman
int engwm[509]; // engaged woman to man

bool fm[509]; // FREE MAN
bool fw[509]; // FREE WOMAN

int n, t, e;

int stableMatching(){
  queue<int> mans;
  int m, m2, w;
  for(int i = 0; i < n; i++){
    fm[i] = true;
    fw[i] = true;
    mans.push(i);
    nm[i] = 0;
  }
  
  while(!mans.empty()){
    m = mans.front();
    mans.pop();
    
    for(; nm[m] < n; nm[m]++){
      w = gm[m][nm[m]];
      
      if(fw[w]){
        fw[w] = false;
        fm[m] = false;
        engmw[m] = w;
        engwm[w] = m;
        
        break;
      }else{
        m2 = engwm[w];
        if(pw[w][m] < pw[w][m2]){
          fm[m2] = true;
          fw[w] = false;
          fm[m] = false;
          engmw[m] = w;
          engwm[w] = m;
          mans.push(m2);
          break;
        }
      }
      
    }
    
    if(fm[m]){
      
      nm[m] = 0;
      mans.push(m);
    }
  }
}


int format(){
  
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      scanf("%d", &gw[e][j]); // WOMAN i: el preferido j
      gw[j][j]--;
      pw[j][gw[e][j]] = j; // WOMAN i: prefiere a gm[e][j] de lugar j
     
    }
  }
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      scanf("%d", &gm[e][j]); // MAN i: la preferida j
      gm[e][j]--;
      pm[e][gm[e][j]] = j; // MAN i: prefiere a gw[e][j] de lugar j
    }
  }
  stableMatching();
  for(int i = 0; i < n; i++){
    printf("%d %d\n", i+1, engmw[i]+1); // print matches
  }

  return 0;
  
}


