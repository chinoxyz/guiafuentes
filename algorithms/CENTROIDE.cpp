#include<cstdio>
#include<cmath>
#include<iostream>

struct point { 
	double x, y; 
};


int N; //Tamano arreglo de puntos
point P[N]; //Arreglo de puntos, que le sobre un espacio!!!!

using namespace std;

point centroid(point P[])
{
	point result;
	int T, N, i;
	double d, A, resX, resY;
	P[N] = P[0], resX = resY = A = 0.0;
	for(i=0; i<N; i++)
	{
		d = P[i].x * P[i+1].y - P[i+1].x * P[i].y;
		A += d;
		resX += (P[i].x + P[i+1].x) * d;
		resY += (P[i].y + P[i+1].y) * d;
	}
	resX /= (3.0 * A);
	resY /= (3.0 * A);
	result.x = resX;
	result.y = resY;
	return result;
}

