const int N = 3e5 + 9, LG = 18;

vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N];
void dfs(int u, int p = 0) {
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (int i = 1; i <= LG; i++) {
    par[u][i] = par[par[u][i - 1]][i - 1];
  }
  for (auto v: g[u]) if (v != p) {
    dfs(v, u);
    sz[u] += sz[v];
  }
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) {
    swap(u, v);
  }
  for (int k = LG; k >= 0; k--) {
    if (dep[par[u][k]] >= dep[v]) {
      u = par[u][k];
    }
  }
  if (u == v) {
    return u;
  }
  for (int k = LG; k >= 0; k--) {
    if (par[u][k] != par[v][k]) {
      u = par[u][k], v = par[v][k];
    }
  }
  return par[u][0];
}

int kth(int u, int k) {                   // kth ancestor of node u
  assert(k >= 0);
  for (int i = 0; i <= LG; i++) {
    if (k & (1 << i)) {
      u = par[u][i];
    }
  }
  return u;
}
int dist(int u, int v) {
  int l = lca(u, v);
  return dep[u] + dep[v] - (dep[l] << 1);
}

int go(int u, int v, int k) {               //kth node from u to v, 0th node is u
  int l = lca(u, v);
  int d = dep[u] + dep[v] - (dep[l] << 1);
  assert(k <= d);
  if (dep[l] + k <= dep[u]) {
    return kth(u, k);
  }
  k -= dep[u] - dep[l];
  return kth(v, dep[v] - dep[l] - k);
}


sample problem : https://cses.fi/paste/f3c3c59a71eb4054a346d8/
sample problem : https://codeforces.com/contest/1328/submission/284013294