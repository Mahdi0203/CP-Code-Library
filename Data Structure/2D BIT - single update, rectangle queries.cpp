#include<bits/stdc++.h>
using namespace std;

#define bug(...) __f(#__VA_ARGS__,__VA_ARGS__); 
template<typename Arg1> void __f(const char* name, Arg1&& arg1){ cout << name << " : " << arg1 << endl;}
template<typename Arg1, typename... Args> void __f(const char* names, Arg1&& arg1, Args&&... args) {const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);}
using ll = long long;

template<typename T>
struct BIT2D {
  int n, m;
  vector<vector<T>> bit;

  BIT2D(int n, int m, vector<vector<T> >&mat) : n(n), m(m) {
    bit.resize(n + 1, vector<T>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        update(i, j, mat[i][j]); // 1-based indexing
      }
    }
  }

  void update(int x, int y, T v) {
    int originalX = x, originalY = y;
    while (x <= n) {
      y = originalY;
      while (y <= m) {
        bit[x][y] += v;
        y += (y & -y);
      }
      x += (x & -x);
    }
  }

  T query(int x, int y) {
    int originalX = x, originalY = y;
    T ans = 0;
    while (x > 0) {
      y = originalY;
      while (y > 0) {
        ans += bit[x][y];
        y -= (y & -y);
      }
      x -= (x & -x);
    }
    return ans;
  }

  T queryRange(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
  }
};

void solve ( int cs ){
  int n, q; cin >> n >> q;
  vector<vector<int>> v(n + 1, vector<int> (n + 1));
  for (int i = 1; i <= n; i++) {
    string s; cin >> s;
    for (int j = 1; j <= n; j++) {
      v[i][j] = (s[j - 1] == '*' ? 1 : 0);
    }
  }

  BIT2D<int> bit(n, n, v);
  while ( q-- ) {
    int tp; cin >> tp;
    if ( tp == 1 ) {
      int x, y; cin >> x >> y;
      auto cur = bit.queryRange(x, y, x, y);
      bit.update(x, y, (cur == 1 ? -1 : 1));
    }
    else {
      int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
      auto cur = bit.queryRange(x1, y1, x2, y2);
      cout << cur << '\n';
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

// https://cses.fi/problemset/result/18840116/
