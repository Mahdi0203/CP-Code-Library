vector<int> (int n){	// sqrt(n)
	vector<int> v;
	for(int i = 2; i * i <= n; i++){
		if(n % i == 0){
			while(n % i == 0){
				v.push_back(i);
				n /= i;
			}
		}
	}
	if(n > 1) v.push_back(n);
	return v;
}