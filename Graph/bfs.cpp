const int inf = 1e9;
const int N = 1e5 + 9;
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

int main(){
  int node, edge; cin >> node >> edge;
  for(int i = 1; i <= edge; i++){
    int u, v; cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  int start;  cin >> start;
  auto dis = bfs(node, start);  // distance from source/starting node
  
}
