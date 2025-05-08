const int N = 1e7 + 7;
bool is_prime[N];

void sieve(){	// O(N / 64)
	for(int i = 2; i < N; i++) is_prime[i] = true;
	for(int i = 2; i * i < N; i++){
		if(is_prime[i]){
			for(int j = i * i; j < N; j += i){
				is_prime[j] = false;
			}
		}
	}
}