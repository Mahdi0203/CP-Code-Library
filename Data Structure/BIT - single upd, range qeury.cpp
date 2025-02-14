template<typename T>
struct BIT {
  int n;
  T neutral_value;
  vector<T> bit;
  function<T(T,T)> combine;

  BIT (int n, vector<T> &arr, T neutral, function<T(T,T)> comb) 
  : n(n), neutral_value(neutral), combine(comb) {
    bit.resize(n + 1, neutral_value);
    for(int i = 1; i <= n; i++) {
      update(i, arr[i]);
    }
  }

  void update(int idx, T val){
    while ( idx <= n ){
      bit[idx] = combine(bit[idx], val);
      idx += (idx & -idx);
    }
  }

  T query(int idx){
    T res = neutral_value;
    while ( idx > 0 ){
      res = combine(res, bit[idx]);
      idx -= (idx & -idx);
    }
    return res;
  }
  T query(int l, int r){
    return query(r) - query(l - 1);
  }
};

/*
Sample : (for calling)
BIT<T> bit(n, arr, Neutral, [](T x,T y){
  return Execution;
});

  T = int or long long

For SUM :       Neutral = 0,                  Execution = x+y
For MIN :       Neutral = INT_MAX,            Execution = min(x,y)
For MAX :       Neutral = INT_MIN,            Execution = max(x,y)
For GCD :       Neutral = 0,                  Execution = __gcd(x, y)
For XOR :       Neutral = 0,                  Execution = x ^ y
For AND :       Neutral = -1,                 Execution = x & y
For OR :        Neutral = 0,                  Execution = x | y
*/