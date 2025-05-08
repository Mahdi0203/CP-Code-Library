int power(int a, int k) {
  int ans = 1;
  while (k) {
    if (k & 1) {
      ans = 1LL * ans * a % mod;
    }
    a = 1LL * a * a % mod;
    k >>= 1;
  }
  return ans;
}
int inverse(int x) {
  return power(x, mod - 2);
}