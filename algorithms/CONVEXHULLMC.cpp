typedef int coord_t;         // coordinate type 
typedef long long coord2_t;  // must be big enough to hold 2*max(|coordinate|)^2 
struct PT { 
  public: 
	int x, y; 
  PT (int _x, int _y){ 
    x = _x; 
    y = _y; 
  } 
  PT(){ 
    x = 0; 
    y = 0; 
  } 
	bool operator <(const PT &p) const { 
		return x < p.x || (x == p.x && y < p.y); 
	} 
	bool operator ==(const PT &p) const { 
		return (x == p.x && y == p.y); 
	} 
	 
}; 

// 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product. 
// Returns a positive value, if OAB makes a counter-clockwise turn, 
// negative for clockwise turn, and zero if the PTs are collinear. 
coord2_t cross(const PT &O, const PT &A, const PT &B){ 
	return (A.x - O.x) * (coord2_t)(B.y - O.y) - (A.y - O.y) * (coord2_t)(B.x - O.x); 
} 

vector<PT> convex_hull(vector<PT> P){ 
	int n = P.size(), k = 0; 
	vector<PT> H(2*n); 
	// Sort PTs lexicographically 
	sort(P.begin(), P.end()); 
	// Build lower hull 
	for (int i = 0; i < n; i++) { 
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--; 
		H[k++] = P[i]; 
	} 
	// Build upper hull 
	for (int i = n-2, t = k+1; i >= 0; i--) { 
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--; 
		H[k++] = P[i]; 
	} 
	H.resize(k); 
	return H; 
}
