#include<bits/stdc++.h>
using namespace std;

#define bug(a) cout << #a << " : " << a <<endl;
using ll = long long;

struct LCT {
  struct Node {              // change node information
    int ch[2]{0, 0}, p = 0;
    bool rev = 0;
    long long val = 0, mx = 0;
  };
  vector<Node> t;
  LCT(int n = 0) { init(n); }
  void init(int n) { t.assign(n + 1, {}); }

  bool isRoot(int x) {
    int p = t[x].p;
    return p == 0 || (t[p].ch[0] != x && t[p].ch[1] != x);
  }
  void push(int x) {        // change this just like SegT push
    if (!x || !t[x].rev) return;
    swap(t[x].ch[0], t[x].ch[1]);
    if (t[x].ch[0]) t[t[x].ch[0]].rev ^= 1;
    if (t[x].ch[1]) t[t[x].ch[1]].rev ^= 1;
    t[x].rev = 0;
  }
  void pull(int x) {        // change this just like SegT pull
    t[x].mx = t[x].val;
    if (t[x].ch[0]) t[x].mx = max(t[x].mx, t[t[x].ch[0]].mx);
    if (t[x].ch[1]) t[x].mx = max(t[x].mx, t[t[x].ch[1]].mx);
  }

  void rotate(int x) {
    int p = t[x].p, g = t[p].p;
    push(p); push(x);
    int d = (t[p].ch[1] == x);
    int b = t[x].ch[d ^ 1];
    if (!isRoot(p)) t[g].ch[t[g].ch[1] == p] = x;
    t[x].p = g;
    t[x].ch[d ^ 1] = p; t[p].p = x;
    t[p].ch[d] = b; if (b) t[b].p = p;
    pull(p); pull(x);
  }
  void splay(int x) {
    static vector<int> stk;
    stk.clear();
    int y = x;
    stk.push_back(y);
    while (!isRoot(y)) { y = t[y].p; stk.push_back(y); }
    while (!stk.empty()) { push(stk.back()); stk.pop_back(); }
    while (!isRoot(x)) {
      int p = t[x].p, g = t[p].p;
      if (!isRoot(p)) {
        ((t[p].ch[0] == x) ^ (t[g].ch[0] == p)) ? rotate(x) : rotate(p);
      }
      rotate(x);
    }
    pull(x);
  }

  void access(int x) {
    int last = 0;
    for (int y = x; y; y = t[y].p) {
      splay(y);
      t[y].ch[1] = last;
      pull(y);
      last = y;
    }
    splay(x);
  }
  void makeRoot(int x) {
    access(x);
    t[x].rev ^= 1;
    push(x);
  }
  int findRoot(int x) {
    access(x);
    while (t[x].ch[0]) {
      push(x);
      x = t[x].ch[0];
    }
    splay(x);
    return x;
  }
  bool connected(int u, int v) {
    if (u == v) return true;
    access(u);
    access(v);
    return t[u].p != 0;
  }
  void link(int u, int v) {
    makeRoot(u);
    if (findRoot(v) != u) {
      t[u].p = v;
    }
  }
  void cut(int u, int v) {
    makeRoot(u);
    access(v);
    if (t[v].ch[0] == u && t[u].ch[1] == 0) {
      t[v].ch[0] = 0;
      t[u].p = 0;
      pull(v);
    }
  }
  long long pathQuery(int u, int v) {      // change query
    makeRoot(u);
    access(v);
    return t[v].mx;
  }
  void setVal(int u, long long val) {      // change update
    access(u);
    t[u].val = val;
    pull(u);
  }
};

void solve ( int cs ){
  int n, q;
  cin >> n >> q;

  LCT lct(n);
  vector<long long> a(n + 1);
  for (int i = 1; i <= n; i++) {    
    cin >> a[i];
    lct.t[i].val = a[i];    // set initial value of nodes
    lct.t[i].mx = a[i];
  }
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    lct.link(u, v);    // connect nodes
  }

  while (q--) {
    int tp; cin >> tp;
    if ( tp == 1 ) {
      int s; long long x;
      cin >> s >> x;
      lct.setVal(s, x);
    } 
    if ( tp == 2 ) {
      int a, b;
      cin >> a >> b;
      cout << lct.pathQuery(a, b) << ' ';
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

// problem : https://cses.fi/problemset/task/2134/
