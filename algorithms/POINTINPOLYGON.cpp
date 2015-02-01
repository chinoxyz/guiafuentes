struct Point { 
  public: 
	int x, y; 
  Point (int _x, int _y){ 
    x = _x; 
    y = _y; 
  } 
  Point(){ 
    x = 0; 
    y = 0; 
  } 
	bool operator <(const Point &p) const { 
		return x < p.x || (x == p.x && y < p.y); 
	} 
	bool operator ==(const Point &p) const { 
		return (x == p.x && y == p.y); 
	} 
	 
}; 

// isLeft(): tests if a point is Left|On|Right of an infinite line.
//    Return: >0 for P2 left of the line through P0 and P1
//            =0 for P2  on the line
//            <0 for P2  right of the line

inline int isLeft( Point P0, Point P1, Point P2 )
{
    return ( (P1.x - P0.x) * (P2.y - P0.y)
            - (P2.x -  P0.x) * (P1.y - P0.y) );
}


// cn_PnPoly(): crossing number test
//      Return:  0 = outside, 1 = inside

int cn_PnPoly( Point P, Point* V, int n )
{
    int    cn = 0;    // the  crossing number counter

    // loop through all edges of the polygon
    for (int i=0; i<n; i++) {    // edge from V[i]  to V[i+1]
       if (((V[i].y <= P.y) && (V[i+1].y > P.y))     // an upward crossing
        || ((V[i].y > P.y) && (V[i+1].y <=  P.y))) { // a downward crossing
            // compute  the actual edge-ray intersect x-coordinate
            float vt = (float)(P.y  - V[i].y) / (V[i+1].y - V[i].y);
            if (P.x <  V[i].x + vt * (V[i+1].x - V[i].x)) // P.x < intersect
                 ++cn;   // a valid crossing of y=P.y right of P.x
        }
    }
    return (cn&1);    // 0 if even (out), and 1 if  odd (in)

}


// wn_PnPoly(): winding number test
//      Return:  wn = the winding number (=0 only when P is outside)
int wn_PnPoly( Point P, Point* V, int n )
{
    int    wn = 0;    // the  winding number counter

    // loop through all edges of the polygon
    for (int i=0; i<n; i++) {   // edge from V[i] to  V[i+1]
        if (V[i].y <= P.y) {          // start y <= P.y
            if (V[i+1].y  > P.y)      // an upward crossing
                 if (isLeft( V[i], V[i+1], P) > 0)  // P left of  edge
                     ++wn;            // have  a valid up intersect
        }
        else {                        // start y > P.y (no test needed)
            if (V[i+1].y  <= P.y)     // a downward crossing
                 if (isLeft( V[i], V[i+1], P) < 0)  // P right of  edge
                     --wn;            // have  a valid down intersect
        }
    }
    return wn;
}

//Si el winding number es 0 -> no esta en el poligono

