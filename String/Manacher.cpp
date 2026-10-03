#include<bits/stdc++.h>
using namespace std;

#define bug(...) __f(#__VA_ARGS__,__VA_ARGS__); 
template<typename Arg1> void __f(const char* name, Arg1&& arg1){ cout << name << " : " << arg1 << endl;}
template<typename Arg1, typename... Args> void __f(const char* names, Arg1&& arg1, Args&&... args) {const char* comma = strchr(names + 1, ','); cout.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);}
using ll = long long;

struct Manacher {
  vector<int> p[2];
  // p[1][i] = (max odd length palindrome centered at i) / 2 [floor division]
  // p[0][i] = same for even, it considers the right center
  // e.g. for s = "abbabba", p[1][3] = 3, p[0][2] = 2
  Manacher(string s) {
    int n = s.size();
    p[0].resize(n + 1);
    p[1].resize(n);
    for (int z = 0; z < 2; z++) {
      for (int i = 0, l = 0, r = 0; i < n; i++) {
        int t = r - i + !z;
        if (i < r) p[z][i] = min(t, p[z][l + t]);
        int L = i - p[z][i], R = i + p[z][i] - !z;
        while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) 
          p[z][i]++, L--, R++;
        if (R > r) l = L, r = R;
      }
    }
  }
  bool is_palindrome(int l, int r) {
    int mid = (l + r + 1) / 2, len = r - l + 1;
    return 2 * p[len % 2][mid] + len % 2 >= len;
  }
};

void solve ( int cs ){
  string s;
  while ( cin >> s ) {
    int n = s.size();

    Manacher mc(s);

    int mx = 0;
    for (int i = 0; i < n; i++) {
      if ( i + mc.p[1][i] + 1 == n ) {
        int len = 2 * mc.p[1][i] + 1;
        mx = max(mx, len);
      }
      if ( i + mc.p[0][i] == n ) {
        int len = 2 * mc.p[0][i];
        mx = max(mx, len);
      }
    }

    int sz = n - mx;
    string res = s;
    for (int i = sz - 1; i >= 0; i--) res += s[i];
    cout << res << '\n';
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

//https://vjudge.net/problem/UVA-11475
