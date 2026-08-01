/*  
  Time Complexity : O(E * sqrt{V})
*/

#include<bits/stdc++.h>
using namespace std;

#define bug(...) __f(#__VA_ARGS__,__VA_ARGS__); 
template<typename Arg1> void __f(const char* name, Arg1&& arg1){ cout << name << " : " << arg1 << endl;}
template<typename Arg1, typename... Args> void __f(const char* names, Arg1&& arg1, Args&&... args) {const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);}
using ll = long long;

const int N = 3e5 + 9;

struct HopcroftKarp {
  static const int inf = 1e9;
  int n;
  vector<int> l, r, d;
  vector<vector<int>> g;
  HopcroftKarp(int _n, int _m) {
    n = _n;
    int p = _n + _m + 1;
    g.resize(p);
    l.resize(p, 0);
    r.resize(p, 0);
    d.resize(p, 0);
  }
  void add_edge(int u, int v) {
    g[u].push_back(v + n); //right id is increased by n, so is l[u]
  }
  bool bfs() {
    queue<int> q;
    for (int u = 1; u <= n; u++) {
      if (!l[u]) d[u] = 0, q.push(u);
      else d[u] = inf;
    }
    d[0] = inf;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : g[u]) {
        if (d[r[v]] == inf) {
          d[r[v]] = d[u] + 1;
          q.push(r[v]);
        }
      }
    }
    return d[0] != inf;
  }
  bool dfs(int u) {
    if (!u) return true;
    for (auto v : g[u]) {
      if(d[r[v]] == d[u] + 1 && dfs(r[v])) {
        l[u] = v;
        r[v] = u;
        return true;
      }
    }
    d[u] = inf;
    return false;
  }
  int maximum_matching() {
    int ans = 0;
    while (bfs()) {
      for(int u = 1; u <= n; u++) if (!l[u] && dfs(u)) ans++;
    }
    return ans;
  }
};

void solve ( int cs ){
  int n, m, k;  cin >> n >> m >> k;

  HopcroftKarp M(n, m);
  for (int i = 1; i <= k; i++) {
    int u, v; cin >> u >> v;
    M.add_edge(u, v);
  }

  int mx = M.maximum_matching();
  cout << mx << '\n';
  for (int u = 1; u <= n; u++) {
    if ( M.l[u] != 0 ) {
      cout << u << ' ' << (M.l[u] - n) << '\n';
    }
  }
}

int main () {

  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int testCase = 1, cs = 0;
  //cin >> testCase;

  while(testCase--){
    solve( ++cs );
  }
  return 0;
}

// https://cses.fi/problemset/result/18176558/
