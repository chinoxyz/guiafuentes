vector<int> KMP(string S, string K){ 
  vector<int> T(K.size() + 1, -1); 
  for(int i = 1; i <= K.size(); i++){ 
    int pos = T[i - 1]; 
    while(pos != -1 && K[pos] != K[i - 1]) pos = T[pos]; 
    T[i] = pos + 1; 
  } 

  vector<int> matches; 
  for(int sp = 0, kp = 0; sp < S.size(); sp++){ 
    while(kp != -1 && (kp == K.size() || K[kp] != S[sp])) 
         kp = T[kp]; 
    kp++; 
    if(kp == K.size()) matches.push_back(sp + 1 - K.size()); 
  } 

  return matches; 
}
