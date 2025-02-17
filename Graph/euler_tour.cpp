ll timer, inTime[N], outTime[N];
vector<ll> flatten;
void euler_tour(int root, int par){
  inTime[root] = timer++;
  flatten.push_back(root);
  for(auto child : g[root]){
    if ( child != par ){
      euler_tour(child, root);
    }
  }
  outTime[root] = timer;
}

int main(){
  // code

  timer = 1;
  flatten.push_back(0);
  euler_tour(1, -1);

  // code
}

sample problem : https://cses.fi/paste/6d2b613367dfad79b89511/
