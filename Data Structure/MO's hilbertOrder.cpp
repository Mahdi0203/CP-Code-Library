#include<bits/stdc++.h>
using namespace std;
 
#define bug(a) cout << #a << " : " << a <<endl;
using ll = long long;
 
const int N = 2e5 + 5;
int cnt, v[N], freq[N];
 
struct Query {
  inline void add(int pos) {
    if (!freq[v[pos]]) cnt++;
    freq[v[pos]]++;
  }
  inline void removee(int pos) {
    freq[v[pos]]--;
    if (!freq[v[pos]]) cnt--;
  }
  inline int getAnswer() {
    return cnt;
  }
};
 
int64_t hilbertOrder(int x, int y, int pow = 21, int rotate = 0) {
  if (pow == 0) return 0;
  int hpow = 1 << (pow - 1);
  int seg = (x < hpow ? 0 : 1) | (y < hpow ? 0 : 2);
  seg = (seg + rotate) & 3;
  static const int rotateDelta[4] = {3, 0, 0, 1};
  int nx = x & (hpow - 1), ny = y & (hpow - 1);
  int nrot = (rotate + rotateDelta[seg]) & 3;
  int64_t subSquareSize = 1LL << (2 * pow - 2);
  int64_t res = seg * subSquareSize;
  int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
  res += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
  return res;
}
 
struct Mos {
  struct Data {
    int l, r, id;
    int64_t ord;
    Data(int _l, int _r, int _id) : l(_l), r(_r), id(_id) {
      ord = hilbertOrder(l, r);
    }
    bool operator < (const Data &p) const {
      return ord < p.ord;
    }
  };
 
  int L, R;
  vector<Data> queries;
  vector<int> ans;
  Query query;
 
  inline void build(int n) {
    L = 1, R = 0;
    queries.clear();
    ans = vector<int>(n + 2, 0);
  }
 
  inline void addQuery(int l, int r, int id) {
    queries.emplace_back(l, r, id);
  }
 
  inline void sortQueries() {
    sort(queries.begin(), queries.end());
  }
 
  inline int solve(int l, int r) {
    while (R < r) query.add(++R);
    while (L > l) query.add(--L);
    while (R > r) query.removee(R--);
    while (L < l) query.removee(L++);
    return query.getAnswer();
  }
 
  inline void solveQueries() {
    for (auto& it : queries) {
      int l = it.l, r = it.r, pos = it.id;
      ans[pos] = solve(l, r);
    }
  }
 
  inline int result(int idx) {
    return ans[idx];
  }
} mos;
 
struct custom_hash {
  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  size_t operator()(uint64_t x) const {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};
 
void solve(int cs) {
  int n, q; cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> v[i];
 
  unordered_map<int, int, custom_hash> mp;
  int id = 0;
  for (int i = 1; i <= n; i++) {
    if (!mp.count(v[i])) {
      mp[v[i]] = ++id;
    }
  }
  for (int i = 1; i <= n; i++) v[i] = mp[v[i]];
 
  mos.build(q);
  cnt = 0;
 
  for (int i = 1; i <= q; i++) {
    int l, r; cin >> l >> r;
    mos.addQuery(l, r, i);
  }
 
  mos.sortQueries();
  mos.solveQueries();
 
  for (int i = 1; i <= q; i++) {
    cout << mos.result(i) << '\n';
  }
}
 
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);
 
  int testCase = 1, cs = 0;
  //cin >> testCase;
 
  while (testCase--) {
    solve(++cs);
  }
 
  return 0;
}

// https://cses.fi/problemset/result/13694540/
