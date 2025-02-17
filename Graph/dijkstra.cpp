vector<ll> dijkstra(int n, int start){      // O(E * log(V))

    vector<ll> dis(n + 1, inf);
    vector<bool> vis(n + 1, false);

    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> pq;
    pq.push({0LL, start});
    dis[start] = 0;

    while( !pq.empty() ){
        int v = pq.top().second;
        ll dis_v = pq.top().first;      // current shortest dis to come node v
        pq.pop();


        if(vis[v]) continue;        // if already done
        vis[v] = true;

        for(auto child : g[v]){
            int u = child.first;
            ll v_u = child.second;              // dis from node v to node u
            if(dis[v] + v_u < dis[u]){
                dis[u] = dis[v] + v_u;
                pq.push({dis[u], u});
            }
        }
    }
    return dis;
}