#include<bits/stdc++.h>
using namespace std;

#define bug(a) cout << #a << " : " << a <<endl;
using ll = long long;

const int N = 2e5 + 5;
const int inf = 1e9;
vector<int> g[N];

vector<int> bfs(int node, int start){
  vector<int> dis(node + 2, inf);

  queue<int> q;
  q.push(start);
  dis[start] = 0;
  while ( !q.empty() ){
    int u = q.front();
    q.pop();
    for(auto v : g[u]){
      if ( dis[u] + 1 < dis[v] ){
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }
  }
  return dis;
}

void solve ( int cs ){
  int n;  cin >> n;
  for(int i = 1; i < n; i++){
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto dis1 = bfs(n, 1);

  int node = -1, mxDis = -1;
  for(int i = 1; i <= n; i++){
    if ( dis1[i] > mxDis ){
      mxDis = dis1[i];
      node = i;
    }
  }

  auto dis2 = bfs(n, node);
  int diameter = 0;
  for(int i = 1; i <= n; i++){
    diameter = max(diameter, dis2[i]);
  }

  cout << diameter << '\n';
}

int main () {

  ios::sync_with_stdio(false);
  cin.tie(NULL); cout.tie(NULL);

  int testCase = 1, cs = 0;
  //cin >> testCase;

  while(testCase--){
    solve( ++cs );
  }
  return 0;
}

problem link : https://cses.fi/paste/a91ae1ceff4d8362b895d5/
