struct st{
  #define lc (node << 1)
  #define rc ((node << 1) + 1)

  ll segT[N * 4], lazy[N * 4];

  st(){                   
    memset( segT, 0, sizeof(segT) );
    memset( lazy, 0, sizeof(lazy) );
  }

  inline void push(int node, int b, int e){
    if( lazy[node] == 0 ) {return;}
    segT[node] += ( lazy[node] * (e - b + 1) );
    if( b != e ){
        lazy[lc] = lazy[lc] + lazy[node];
        lazy[rc] = lazy[rc] + lazy[node];
    }
    lazy[node] = 0;
  }
  inline ll combine( ll a, ll b ){
    return a + b;       // change this
  }
  inline void pull(int node){
    segT[node] = segT[lc] + segT[rc];
  }

  void build(int node, int b, int e){
    lazy[node] = 0;     // change this
    if( b == e ){
      segT[node] = a[b];
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    pull(node);
  }

  void upd(int node, int b, int e, int i, int j, ll val){
    push(node, b, e);
    if( b > j || e < i ) {return;}
    if( b >= i && e <= j ){
      lazy[node] = val;       // set lazy
      push(node, b, e);
      return;
    }
    int mid = (b + e) >> 1;
    upd(lc, b, mid, i, j, val);
    upd(rc, mid + 1, e, i, j, val);
    pull(node);
  }

  ll query(int node, int b, int e, int i, int j){
    push(node, b, e);
    if( b > j || e < i ) {return 0;}
    if( b >= i && e <= j ){
      return segT[node];
    }
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }

} segT;