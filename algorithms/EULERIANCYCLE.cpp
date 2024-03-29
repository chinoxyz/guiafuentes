const int mn = 1e5+9;
vector<int> g[mn];
vector<int> ge[mn];
vector<int> eulerian_path(int ini, int n){
  for(int i = 0; i < n; i++){
    ge[i] = g[i];
  }
  vector<int> res;
  vector<int> st;
  st.push_back(ini);
  while (!st.empty()) {
    int v = st.back();
    if (ge[v].empty()) {
      res.push_back(v);
      st.pop_back();
    } else {
      st.push_back(ge[v].back());
      ge[v].pop_back();
    }
  }
  reverse(res.begin(), res.end());
  return res;
}

