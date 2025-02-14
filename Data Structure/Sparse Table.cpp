template<typename T>
struct SparseTable {
  vector<vector<T>> sparse_table;
  vector<int> lg;
  function<T(T, T)> combine;

  SparseTable(int n, const vector<T>& arr, function<T(T, T)> comb) : combine(comb) {
    lg.resize(n + 1);
    sparse_table.resize(log2(n) + 1, vector<T>(n + 1));
    calculateLog(n);
    initTable(n, arr);
    build(n);
  }

  void calculateLog(int n) {
    lg[1] = 0;
    for(int i = 2; i <= n; i++) {
      lg[i] = lg[i / 2] + 1;
    }
  }

  void initTable(int n, const vector<T>& arr) {
    for(int i = 1; i <= n; i++) {
      sparse_table[0][i] = arr[i];
    }
  }

  void build(int n) {
    for(int i = 1; i <= lg[n]; i++) {
      for(int j = 1; j + (1 << i) - 1 <= n; j++) {
        sparse_table[i][j] = combine(sparse_table[i - 1][j], sparse_table[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  T query(int l, int r) {
    int len = r - l + 1;
    int j = lg[len];
    return combine(sparse_table[j][l], sparse_table[j][r - (1 << j) + 1]);
  }
};

/**

Sample :
  SparseTable<T> st(n,arr,[](T x,T y)
  {
    return Execution;
  });

      T = int or long long
      
For MIN :       Execution = min(x,y)
For MAX :       Execution = max(x,y)
For GCD :       Execution = __gcd(x, y)
For XOR :       Execution = x ^ y
For AND :       Execution = x & y
For OR :        Execution = x | y

**/

sample problem 1 : https://cses.fi/paste/d31095437015bf7bb7c36a/
sample problem 2 : https://codeforces.com/contest/2050/submission/305559195