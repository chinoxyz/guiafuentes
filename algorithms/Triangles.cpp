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
};

int n, idx[MAXN], inv[MAXN];
vector<Point> p;

class Event {
  public:
  int i, j, dx, dy, right, left;

  Event(int _i, int _j) {
    i = _i;
    j = _j;
    dx = p[i].x - p[j].x;
    dy = p[i].y - p[j].y;
    if (dy == 0 && dx < 0)
      dx = -dx;
    else if (dy < 0) {
      dx = -dx;
      dy = -dy;
    }
    left = min(p[i].x, p[j].x);
    right = max(p[i].x, p[j].x);
  }
  
  bool operator<(const Event &o) const {
    int temp = dy * o.dx - dx * o.dy;
    if (temp == 0) temp = left - o.left;
    if (temp == 0) temp = right - o.right;
    return (temp < 0);
  }
};

vector<Event> e;

int twiceArea(Point a, Point b, Point c) {
  return fabs((a.x - c.x) * (b.y - c.y) - (a.y - c.y) * (b.x - c.x));
}

bool compare(int f, int g) {
  int dy = p[f].y - p[g].y;
  int r = (dy == 0 ? (p[f].x - p[g].x) : dy);
  return (r < 0);
}

// Return the min area and the max area
pair<double,double> solve() {
  e.clear();
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      e.pb(Event(i, j));
      
  sort(e.begin(), e.end());
  
  for (int i = 0; i < n; i++)
    idx[i] = i;
  
  sort(idx, idx+n, compare);
  
  for (int i = 0; i < n; i++)
    inv[idx[i]] = i;
  
  int bestmin = inf, bestmax = -1, k;
  
  for (int i = 0; i < e.size(); i++) {
    k = min(inv[e[i].i], inv[e[i].j]) - 1;
    if (k > -1) {
      bestmin = min(twiceArea(p[e[i].i], p[e[i].j], p[idx[k]]), bestmin);
      bestmax = max(twiceArea(p[e[i].i], p[e[i].j], p[idx[0]]), bestmax);
    }
    k = max(inv[e[i].i], inv[e[i].j]) + 1;
    if (k < n) {
      bestmin = min(twiceArea(p[e[i].i], p[e[i].j], p[idx[k]]), bestmin);
      bestmax = max(twiceArea(p[e[i].i], p[e[i].j], p[idx[n - 1]]), bestmax);
    }
    k = idx[inv[e[i].i]];
    idx[inv[e[i].i]] = idx[inv[e[i].j]];
    idx[inv[e[i].j]] = k;
    k = inv[e[i].i];
    inv[e[i].i] = inv[e[i].j];
    inv[e[i].j] = k;
  }
  return mp(bestmin/2.0, bestmax/2.0);
}

void init(vector<Point> ve){
  p = ve;
}
