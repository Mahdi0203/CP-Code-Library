#include<bits/stdc++.h>
using namespace std;

#define bug(a) cout<< #a << " : " << a <<endl;
using ll = long long;

__int128 read(){
  string s;
  cin >> s;
  __int128 x = 0;
  for(auto c : s){
    x = (x * 10) + (c - '0');
  }
  return x;
}

string to_string(__int128 x){
  string s = "";
  while(x){
    s += (char)(x % 10 + '0');
    x /= 10;
  }
  reverse(s.begin(), s.end());
  return s;
}

void write(__int128 x){
  cout << to_string(x) << '\n';
}

void solve( int cs ){
  __int128 x = read(), y = read();
  __int128 ans = x + y;
  write(ans);
}

int main(){

  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int testCase = 1, cs = 0;
  //cin >> testCase;

  while(testCase--){
    solve( ++cs );
  }

}