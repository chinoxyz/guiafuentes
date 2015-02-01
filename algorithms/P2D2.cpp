#include <iostream>
#include <cstdio>
#include <cmath>

/* Point 2d {{{ */
typedef double pdata;
struct p2d {
	pdata x, y;
	p2d operator-(p2d p){ return p2d(x - p.x, y - p.y); } //Resta vectores
	pdata  operator*(p2d p){ return (x * p.y - y * p.x);} //Producto cruz, recibe un point
	bool operator==(p2d p){ return (x == p.x && y == p.y);} //Igualdad puntos
	bool point_on_line(p2d p0, p2d p1){ return ((p1 - p0) * (*this - p0)) == 0;} //Pto en la linea, sirve para collineal
	double dist(p2d p){ return hypot(x - p.x, y - p.y); } //Distancia Entre dos puntos

	p2d(pdata _x = 0, pdata _y = 0): x(_x), y(_y) {};
};
/* }}} */

/* Line 2d {{{ */
struct line {
	pdata A, B, C;
	line(p2d X, p2d Y): A(Y.y - X.y), B(X.x - Y.x), C((this->A)*X.x + (this->B)*X.y) {};
};
/* }}} */

//Retorna la interseccion, en casos de ser linea paralelas retornara un punto con (inf,inf)
p2d line_line_intersect(line L1, line L2) {
	p2d R;
	
	double det = L1.A*L2.B - L2.A*L1.B;
    if(det == 0){
        //Lineas paralelas
        R.x = 0x3f3f3f;
        R.y = 0x3f3f3f;
    }else{	
        R.x = (L2.B*L1.C - L1.B*L2.C)/det; //X
        R.y = (L1.A*L2.C - L2.A*L1.C)/det; //Y
    }
    
    return R;
}  

//Observacion: Para el caso de inters. de segmentos, basta ver si el pto de la interseccion basta con que se chequee si estan en el rango de los X e Y del segmento, en caso que fuese uno de ellos un segmento, o de ambos.


// Recibe 3 puntos y retorna el centro del circulo, el radio se saca con la distacia del centro a cualquiera
// de los 3 ptos.
p2d circle_3_points( p2d X, p2d Y, p2d Z ) {
	line L1 = line(X,Y);
	line L2 = line(Y,Z);
	p2d MedioXY = p2d((X.x + Y.x)/2, (X.y + Y.y)/2);
	p2d MedioYZ = p2d((Y.x + Z.x)/2, (Y.y + Z.y)/2);
	double D1 = (-L1.B)*MedioXY.x + L1.A*MedioXY.y;
	double D2 = (-L2.B)*MedioYZ.x + L2.A*MedioYZ.y;
	double A;
	A = L1.A;
	L1.A = -L1.B;
	L1.B = A; 
	L1.C = D1;
	A = L2.A;
	L2.A = -L2.B;
	L2.B = A; 
	L2.C = D2;
	return line_line_intersect(L1,L2);
}


