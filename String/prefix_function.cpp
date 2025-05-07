// returns the longest proper prefix array of pattern p
// where lps[i]=longest proper prefix which is also suffix of p[0...i]
vector<int> pref_func(vector<int> p) {
  int sz = p.size();
  vector<int> pi;
  pi.assign(sz + 1, 0);
  int j = 0;
  pi[0] = 0;
  for(int i = 1; i < sz; i++) {
    while(j >= 0 && p[i] != p[j]) {
      if(j >= 1) j = pi[j - 1];
      else j = -1;
    }
    j++;
    pi[i] = j;
  }
  return pi;
}

sample problem : https://codeforces.com/contest/471/submission/318689537