ll mulmod(ll x, ll y, ll mod){   // O(log y)
    ll ans = 1 % mod;
    while(y){
        if(y & 1){
            ans = (ans + x) % mod;
        }
        x = (x + x) % mod;   
        y >>= 1;
    }
    return ans;
}

// long long mulmod(long long x, long long y, long long mod) { // O(1)
//   return (long long)((__int128)x * y % mod);
// }