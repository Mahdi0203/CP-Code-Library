int power(int x, ll n, int mod){
	if(n == 0) return (1 % mod);
	int cur = power(x, (n / 2), mod);
	if(n & 1){
		return (1LL * cur * cur % mod) * x % mod;
	}
	else{
		return (1LL * cur * cur) % mod;
	}
}