#include<bits/stdc++.h>
using namespace std;

#define bug(...) __f(#__VA_ARGS__,__VA_ARGS__); 
template<typename Arg1> void __f(const char* name, Arg1&& arg1){ cout << name << " : " << arg1 << endl;}
template<typename Arg1, typename... Args> void __f(const char* names, Arg1&& arg1, Args&&... args) {const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);}
using ll = long long;

const int N = 3e4 + 9, LG = 18, inf = 1e9 + 9;

struct ST {
#define lc (n << 1)
#define rc ((n << 1) | 1)
  ll t[4 * N], lazy[4 * N];
  ST() {
    fill(t, t + 4 * N, -inf);
    fill(lazy, lazy + 4 * N, -1);
  }
  inline void push(int n, int b, int e) {
    if(lazy[n] == -1) return;
    t[n] = lazy[n];
    if(b != e) {
      lazy[lc] = lazy[n];
      lazy[rc] = lazy[n];
    }
    lazy[n] = -1;
  }
  inline ll combine(ll a, ll b) {
    return (a + b); //merge left and right queries
  }
  inline void pull(int n) {
    t[n] = (t[lc] + t[rc]); //merge lower nodes of the tree to get the parent node
  }
  void build(int n, int b, int e) {
    if(b == e) {
      t[n] = 0;
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    pull(n);
  }
  void upd(int n, int b, int e, int i, int j, int v) {
    push(n, b, e);
    if(j < b || e < i) return;
    if(i <= b && e <= j) {
      lazy[n] = v;
      push(n, b, e);
      return;
    }
    int mid = (b + e) >> 1;
    upd(lc, b, mid, i, j, v);
    upd(rc, mid + 1, e, i, j, v);
    pull(n);
  }
  ll query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if(i > e || b > j) return 0;
    if(i <= b && e <= j) return t[n];
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
} t;

vector<int> g[N];
int par[N][LG + 1], dep[N], sz[N];
void dfs(int u, int p = 0) {
  par[u][0] = p;
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (int i = 1; i <= LG; i++) par[u][i] = par[par[u][i - 1]][i - 1];
  if (p) g[u].erase(find(g[u].begin(), g[u].end(), p));
  for (auto &v : g[u]) if (v != p) {
      dfs(v, u);
      sz[u] += sz[v];
      if(sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
    }
}
int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  for (int k = LG; k >= 0; k--) if (dep[par[u][k]] >= dep[v]) u = par[u][k];
  if (u == v) return u;
  for (int k = LG; k >= 0; k--) if (par[u][k] != par[v][k]) u = par[u][k], v = par[v][k];
  return par[u][0];
}
int kth(int u, int k) {
  // assert(k >= 0);
  for (int i = 0; i <= LG; i++) if (k & (1 << i)) u = par[u][i];
  return u;
}
int T, head[N], st[N], en[N];
void dfs_hld(int u) {
  st[u] = ++T;
  for (auto v : g[u]) {
    head[v] = (v == g[u][0] ? head[u] : v);
    dfs_hld(v);
  }
  en[u] = T;
}
int n;
ll query_up(int u, int v) {
  ll ans = 0;
  while(head[u] != head[v]) {
    ans += t.query(1, 1, n, st[head[u]], st[u]);
    u = par[head[u]][0];
  }
  ans += t.query(1, 1, n, st[v], st[u]);
  return ans;
}
ll query(int u, int v) {
  int l = lca(u, v);
  ll ans = query_up(u, l);
  if (v != l) ans += query_up(v, kth(v, dep[v] - dep[l] - 1));
  return ans;
}
void update_path(int u, int v, ll x) {
  while (head[u] != head[v]) {
    if (dep[head[u]] < dep[head[v]]) {
      swap(u, v);
    }

    t.upd(1, 1, n, st[head[u]], st[u], x);
    u = par[head[u]][0];
  }
  if (dep[u] > dep[v]) {
    swap(u, v);
  }
  t.upd(1, 1, n, st[u], st[v], x);
}

void clean(int n) {
  for (int i = 0; i <= n; i++) {
    g[i].clear();
    T = head[i] = st[i] = en[i] = dep[i] = sz[i] = 0;
    for (int j = 0; j <= LG; j++) par[i][j] = 0;
  }
}
void solve ( int cs ){
  cin >> n;
  vector<int> v(n + 1);
  for (int i = 1; i <= n; i++) cin >> v[i];
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    ++u, ++v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs(1);
  head[1] = 1;
  dfs_hld(1);

  t.build(1, 1, n);
  for (int i = 1; i <= n; i++) t.upd(1, 1, n, st[i], st[i], v[i]);

  int q;  cin >> q;
  cout << "Case " << cs << ":" << '\n';
  while ( q-- ) {
    int tp; cin >> tp;
    if ( !tp ) {
      int u, v; cin >> u >> v;
      cout << query(++u, ++v) << '\n';
    }
    else {
      int u, x; cin >> u >> x;
      ++u;
      t.upd(1, 1, n, st[u], st[u], x);
    }
  }
  clean(n);
}


int main () {

  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int testCase = 1, cs = 0;
  cin >> testCase;

  while(testCase--){
    solve( ++cs );
  }
  return 0;
}

// https://lightoj.com/submission/3567306
