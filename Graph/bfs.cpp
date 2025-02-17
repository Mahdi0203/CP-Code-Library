const int inf = 1e9;
const int N = 1e5 + 9;
vector<int> g[N];

vector<int> bfs(int node, int start){
  vector<int> dis(node + 2, inf);
  vector<bool> dis(node + 2, false);
  queue<int> q;
  q.push(start);
  dis[start] = 0;
  vis[start] = true;
  while ( !q.empty() ){
    int u = q.top();
    q.pop();
    for(auto v : g[u]){
      if ( !vis[v] ){
        vis[v] = true;
        dis[v] = dis[u] + 1;
        q.push(v);
      }
    }
  }
}

int main(){
  int node, edge; cin >> node >> edge;
  for(int i = 1; i <= edge; i++){
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  auto dis = bfs(1);  // distance from source/starting node
  
}