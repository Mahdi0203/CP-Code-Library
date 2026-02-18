struct st {
  ll segT[N * 4];
  static const int inf = 1e9;

  st(){
    memset( segT, 0, sizeof(segT) );
  }
  inline void pull(int node, int lc, int rc){    // change this function according to what you need 
    segT[node] = max(segT[lc], segT[rc]);
  }
  void build(int node, int b, int e){
    if( b == e ){
      segT[node] = arr[e];
      return;
    }
    int mid = (b + e) >> 1;
    int lc = (node << 1), rc = (node << 1) + 1;
    build( lc, b, mid );
    build( rc, mid + 1, e );
    pull( node, lc, rc );
  }
  void upd(int node, int b, int e, int i, int val){
    if( b > i || e < i ) {return;}
    if( b == e && e == i ){
      segT[node] += val;      // set according to problem
      return;
    }
    int mid = (b + e) >> 1;
    int lc = (node << 1), rc = (node << 1) + 1;
    upd( lc, b, mid, i, val);
    upd( rc, mid + 1, e, i, val);
    pull( node, lc, rc );
  }
  ll query(int node, int b, int e, int i, int j){
    if( b > j || e < i ) {return -inf;}      // return a neutral value according to problem
    if( b >= i && e <= j ) {return segT[node];}
    int mid = (b + e) >> 1;
    int lc = (node << 1), rc = (node << 1) + 1;
    ll L = query(lc, b, mid, i, j);
    ll R = query(rc, mid + 1, e, i, j);
    return max(L, R);       
  }

} segT;
