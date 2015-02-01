// KNUTH OPTIMIZATION FOR BREAKING STRINGS  

for (int s = 0; s<=k; s++){              //s - length(size) of substring
  for (int l = 0; l+s<=k; l++) {         //l - left point
    int r = l + s;                       //r - right point
    if (s < 2) {                              
      res[l][r] = 0;                     //DP base - nothing to break
      mid[l][r] = l;                     //mid is equal to left border
      continue;
    }
    int mleft = mid[l][r-1];             //Knuth's trick: getting bounds on m
    int mright = mid[l+1][r];
    res[l][r] = linf;
    for (int m = mleft; m<=mright; m++) {//iterating for m in the bounds only
      lint tres = res[l][m] + res[m][r] + (x[r]-x[l]);
      if (res[l][r] > tres) {            //relax current solution
        res[l][r] = tres;
        mid[l][r] = m;
      }
    }
  }
}
lint answer = res[0][k];



