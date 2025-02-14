struct Query{                         // operations depends on problem
  inline void add(int pos) {          // insert to right site (R)
    
  }

  inline void removee(int pos) {       // remove from left site (L)
    
  }

  inline ll getAnswer() {
    
  }

  inline void reset(int n){
    
  }
};

struct Mos {
  struct Data{
    int l, r, id, blcl, blcr;
    Data(int _l, int _r, int _id, int block){
      l = _l, r = _r, id = _id,  blcl = l / block, blcr = r / block;
    }
    bool operator < (const Data &p) const {
      if(blcl != p.blcl) {return l < p.l;}
      if(blcr != p.blcr) {return r < p.r;}
      return r < p.r;
    }
  };

  int res,L,R,blockSize;
  vector<Data>queries;
  vector<int>ans;           // Change (int to long long) according to preference
  Query query;

  inline void build(int n){
    res=0,L=1,R=0;
    blockSize = sqrt(n);
    queries.clear();
    ans = vector<int>(n + 2, 0);
  }

  inline void addQuery(int l,int r,int id) {
    queries.push_back(Data(l,r,id,blockSize));
  }

  inline void sortQueries() {
    sort(queries.begin(),queries.end());
  }

  inline int solve(int l,int r) {
    while(R < r) {query.add(++R);}
    while(L > l) {query.add(--L);}
    while(R > r) {query.removee(R--);}
    while(L < l) {query.removee(L++);}

    return query.getAnswer();
  }

  inline void solveQueries() {
    for(auto it:queries) {
      int l = it.l;
      int r = it.r;
      int pos = it.id;
      ans[pos] = solve(l,r);
    }
  }

  inline int result(int idx) {
    return ans[idx];
  }

  inline void reset(int n) {
    query.reset(n);
  }
} mos;


// sample 1 : https://codeforces.com/contest/86/submission/303177841