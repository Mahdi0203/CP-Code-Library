/* 
  In the residual graph, an edge [u,v] has remaining capacity if (e.w - e.flow) > 0.
  Then [u, v] is in Source side.
  Time Complexity: O(V^2 * E)
*/

#include<bits/stdc++.h>
using namespace std;

#define bug(...) __f(#__VA_ARGS__,__VA_ARGS__); 
template<typename Arg1> void __f(const char* name, Arg1&& arg1){ cout << name << " : " << arg1 << endl;}
template<typename Arg1, typename... Args> void __f(const char* names, Arg1&& arg1, Args&&... args) {const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);}
using ll = long long;

const long long inf = 1LL << 61;
struct Dinic {
  struct edge {
    int to, rev;
    long long flow, w;
    int id;
  };
  int n, s, t, mxid;
  vector<int> d, flow_through;
  vector<int> done;
  vector<vector<edge>> g;
  Dinic() {}
  Dinic(int _n) {
    n = _n + 10;
    mxid = 0;
    g.resize(n);
  }
  void add_edge(int u, int v, long long w, int id = -1) {
    edge a = {v, (int)g[v].size(), 0, w, id};
    edge b = {u, (int)g[u].size(), 0, w, -2}; //for bidirectional edges cap(b) = w
    g[u].emplace_back(a);
    g[v].emplace_back(b);
    mxid = max(mxid, id);
  }
  bool bfs() {
    d.assign(n, -1);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto &e : g[u]) {
        int v = e.to;
        if (d[v] == -1 && e.flow < e.w) d[v] = d[u] + 1, q.push(v);
      }
    }
    return d[t] != -1;
  }
  long long dfs(int u, long long flow) {
    if (u == t) return flow;
    for (int &i = done[u]; i < (int)g[u].size(); i++) {
      edge &e = g[u][i];
      if (e.w <= e.flow) continue;
      int v = e.to;
      if (d[v] == d[u] + 1) {
        long long nw = dfs(v, min(flow, e.w - e.flow));
        if (nw > 0) {
          e.flow += nw;
          g[v][e.rev].flow -= nw;
          return nw;
        }
      }
    }
    return 0;
  }
  long long max_flow(int _s, int _t) {
    s = _s;
    t = _t;
    long long flow = 0;
    while (bfs()) {
      done.assign(n, 0);
      while (long long nw = dfs(s, inf)) flow += nw;
    }
    flow_through.assign(mxid + 10, 0);
    for(int i = 0; i < n; i++) for(auto e : g[i]) if(e.id >= 0) flow_through[e.id] = e.flow;
    return flow;
  }
  vector<bool> get_cut_side() {
    vector<bool> visited(t + 20, false);
    queue<int> q;
    
    q.push(s);
    visited[s] = true;
    
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      
      for (const auto &e : g[u]) {
        if (!visited[e.to] && e.w - e.flow > 0) {
          visited[e.to] = true;
          q.push(e.to);
        }
      }
    }
    return visited;
  }

};


void solve ( int cs ){
  int n, m; cin >> n >> m;

  int s = 0, t = n + 1;
  Dinic dc = Dinic(t);
  vector<pair<int,int>> ed;
  for (int i = 1; i <= m; i++) {
    int u, v; cin >> u >> v;
    dc.add_edge(u, v, 1);
    ed.push_back({u, v});
  }

  dc.add_edge(s, 1, 1e4);
  dc.add_edge(n, t, 1e4);

  int mx = dc.max_flow(0, n + 1);
  cout << mx << '\n';

  auto vis = dc.get_cut_side();
  
  for (auto [u, v] : ed) {
    if( (vis[u] and !vis[v]) or (!vis[u] and vis[v])) cout << u << ' ' << v << '\n';
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

// https://cses.fi/problemset/result/18176435/
