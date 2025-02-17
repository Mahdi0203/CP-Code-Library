#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 6;
vector<int> g[N];
int connected_component, vis[N];
void dfs(int root){
	vis[root] = true;
	for(auto child : g[root]){
		if ( !vis[child] ) {
			dfs(child);
		}
	}
}

int main () {
	int node, edge;	cin >> node >> edge;
	for(int i = 1; i <= edge; i++){
		int u, v;	cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	connected_component = 0;
	for(int i = 1; i <= node; i++){
		if ( !vis[i] ){
			dfs(i);
			connected_component++;
		}
	}
	cout << connected_component << '\n';

	return 0;
}

// returns number of connectec component.