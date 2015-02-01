namespace aho { // aho-Corasick's algorithm
    const int MAXN = 3000005;
    map<char, int> g[MAXN];
    int f[MAXN]; // failure
    vector<int> output[MAXN];
    int n; // state count
    vector<string> plants;
    
    
    // n should be the sum of the lenghts of all substrings
    void reset() {
        n = 1;
        g[0].clear();
        output[0].clear();
        f[0] = 0;
        plants.clear();
    }
    // add s
    void add(const char *s) {
        int state = 0;
        int id = plants.size();
        plants.push_back(string(s));
        for (int i = 0; s[i]; i++) {
            char c = s[i];
            if (g[state].count(c) == 0) {
                g[state][c] = n;
                g[n].clear();
                output[n].clear();
                f[n] = -1;
                n++;
            }
            state = g[state][c];
        }
        output[state].push_back(id);
    }
    
    void prepare() { // the BFS step
        queue<int> q;
        f[0] = 0;
        for (char c = 'A'; c <= 'z'; ++c) {
            if (g[0].count(c) == 0) {
                g[0][c] = 0;
            } else {
                int s = g[0][c];
                f[s] = 0;
                q.push(s);
            }
        }
        
        while (q.size() > 0) {
            int u = q.front(); q.pop();
            for (map<char, int>::iterator i = g[u].begin(); i != g[u].end(); ++i) {
                char label = i->first;
                int node = i->second;
                f[node] = f[u];
                while (g[f[node]].count(label) == 0) {
                    f[node] = f[f[node]];
                }
                f[node] = g[f[node]][label];
                output[node].insert(output[node].end(), output[f[node]].begin(), output[f[node]].end());
                q.push(node);
            }
        }   
    }
    
    int next_state(int state, char label) {
        while (g[state].count(label) == 0) {
            state = f[state];
        }
        return g[state][label];
    }
    // Todos los substring de id
    vector<int> subs(int id){
      string &s = plants[id];
      vector<int> res;
      int state = 0;
      for (int k = 0; k < s.size(); ++k) {
          char next = s[k];
          state = next_state(state, next);
          for (int e = 0; e < output[state].size(); ++e) {
              int to = output[state][e];
              if (plants[to].size() < s.size()) { // found a proper substring
                  res.push_back(to);
              }
          }
      }
      return res;
    }
    
}
