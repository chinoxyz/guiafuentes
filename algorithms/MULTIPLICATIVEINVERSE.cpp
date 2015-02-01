typedef long long lint;
inline lint mod_mult_inverse(lint a, lint m){

    lint x = 0, lastx = 1;
    lint y = 1, lasty = 0;

    lint b = m;
    lint aux;
    while( b!=0 ){
        lint quotient = a/b;
        lint aux;
        //{a, b} = {b, a bod b}
        aux = b;
        b = a%b;
        a = aux;
        //{x, lastx} = {lastx - quotient*x, x}
        aux = x;
        x = lastx - quotient*x;
        lastx = aux;
        //{y, lasty} = {lasty - quotient*y, y}        
        aux = y;
        y = lasty - quotient*y;
        lasty = aux;
    }
    if(a!=1)
        return 0;
    x = lastx;
    if( x < 0 )
        return x + m;
    return x;
}
