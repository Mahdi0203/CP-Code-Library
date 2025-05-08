int power(int x, int n, int mod){   // O(log n)
  int ans = 1 % mod;
  while(n){
    if(n & 1){
      ans = (1LL * ans * x) % mod;
    }
    x = (1LL * x * x) % mod;   
    n >>= 1;
  }
  return ans;
}