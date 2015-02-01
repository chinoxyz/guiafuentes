long long mul(long long a,long long b,long long c){
    long long x = 0,y=a%c;
    while(b > 0){
        if(b%2 == 1){
            x = (x+y)%c;
        }
        y = (y*2)%c;
        b /= 2;
    }
    return x%c;
}
 
long long mod(long long a,long long b,long long c){
    long long x=1,y=a; 
    while(b > 0){
        if(b%2 == 1){
            x=mul(x,y,c);
        }
        y = mul(y,y,c); 
        b /= 2;
    }
    return x%c;
}
  
bool Miller(long long p,long long it){
    if(p<2){
        return false;
    }
    if(p!=2 && p%2==0){
        return false;
    }
    long long s=p-1;
    while(s%2==0){
        s/=2;
    }
    for(long long i=0;i<it;i++){
        long long a=rand()%(p-1)+1,tt=s;
        long long md=mod(a,tt,p);
        while(tt!=p-1 && md!=1 && md!=p-1){
            md=mul(md,md,p);
            tt *= 2;
        }
        if(md!=p-1 && tt%2==0){
            return false;
        }
    }
    return true;
}
