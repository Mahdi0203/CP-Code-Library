#include<bits/stdc++.h>
using namespace std;

#define bug(...) __f(#__VA_ARGS__,__VA_ARGS__); 
template<typename Arg1> void __f(const char* name, Arg1&& arg1){ cout << name << " : " << arg1 << endl;}
template<typename Arg1, typename... Args> void __f(const char* names, Arg1&& arg1, Args&&... args) {const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);}
using ll = long long;
const int N = 1e5 + 9, LG = 18;

vector<int> g[N];
vector<pair<int,int>> g1[N];
int par[N][LG + 1], dep[N], sz[N], cost[N];
int MN[N][LG + 1], MX[N][LG + 1];

void cal(int u, int p = 0) {  // problem requirement
  for (auto [v, w] : g1[u]) {
    if ( v == p ) continue;
    cost[v] = w;
    cal(v, u);
  }
}

void dfs(int u, int p = 0) {
  par[u][0] = p;
  MX[u][0] = MN[u][0] = cost[u];
  dep[u] = dep[p] + 1;
  sz[u] = 1;
  for (int i = 1; i <= LG; i++) {
    par[u][i] = par[par[u][i - 1]][i - 1];
    MX[u][i] = max(MX[par[u][i - 1]][i - 1], MX[u][i - 1]);
    MN[u][i] = min(MN[par[u][i - 1]][i - 1], MN[u][i - 1]);
  }

  for (auto v: g[u]) if (v != p) {
    dfs(v, u);
    sz[u] += sz[v];
  }
}

pair<int,int> query(int u, int v) {    // binary lifting
  int mn = 1e8, mx = -1;
  if ( dep[u] < dep[v] ) swap(u, v);
  for (int k = LG; k >= 0; k--) {
    if ( dep[par[u][k]] >= dep[v] ) {
      mn = min(mn, MN[u][k]);
      mx = max(mx, MX[u][k]);
      u = par[u][k];
    }
  }
  if ( u == v ) return {mn, mx};

  for (int k = LG; k >= 0; k--) {
    if ( par[u][k] != par[v][k] ) {
      mn = min({mn, MN[u][k], MN[v][k]});
      mx = max({mx, MX[u][k], MX[v][k]});
      u = par[u][k];
      v = par[v][k];
    }
  }
  mn = min({mn, MN[u][0], MN[v][0]});
  mx = max({mx, MX[u][0], MX[v][0]});
  return {mn, mx};
}

void clean(int n) {
  for (int i = 1; i <= n; i++) {
    g[i].clear(), g1[i].clear();
    dep[i] = sz[i] = cost[i] = 0;
    for (int k = 0; k <= LG; k++) {
      par[i][k] = MN[i][k] = MX[i][k] = 0;
    }
  }
}
void solve ( int cs ){
  int n;  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v, w;  cin >> u >> v >> w;
    g[u].push_back(v);
    g[v].push_back(u);
    
    g1[u].push_back({v, w});
    g1[v].push_back({u, w});
  }

  cal(1);
  dfs(1);

  int q;  cin >> q;
  cout << "Case " << cs << ":" << '\n';
  while ( q-- ) {
    int u, v; cin >> u >> v;
    auto [mn, mx] = query(u, v);
    cout << mn << ' ' << mx << '\n';
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

// https://lightoj.com/submission/3569104
