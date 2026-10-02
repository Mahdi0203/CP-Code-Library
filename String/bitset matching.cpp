#include<bits/stdc++.h>
using namespace std;

#define bug(a) cout << #a << " : " << a <<endl;
using ll = long long;

const int N = 1e5 + 5;

void solve ( int cs ){
  string s; cin >> s;
  int n = s.size();

  bitset<N> bs[26], set;
  for (int i = 0; i < n; i++) {             
    bs[s[i] - 'a'][i] = 1;
    set[i] = 1;
  }

  int q;  cin >> q;
  while ( q-- ) {
    int tp; cin >> tp;

    if ( tp == 1) {
      int idx; char ch; 
      cin >> idx >> ch;
      idx--;
      bs[s[idx] - 'a'][idx] = 0;
      s[idx] = ch;
      bs[ch - 'a'][idx] = 1;
    }
    else {
      int l, r; string s1;
      cin >> l >> r >> s1;
      l--, r--;
      if ( r - l + 1 < s1.size() ) {
        cout << 0 << '\n';
        continue;
      }
      bitset<N> same = set;
      for (int i = 0; i < s1.size(); i++) {
        same &= (bs[s1[i] - 'a'] >> (i));
      }
      
      int L = (same >> (l)).count();
      int R = (same >> (r - s1.size() + 2)).count();
      cout << (L - R) << '\n';
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

// https://codeforces.com/contest/914/submission/318535139
