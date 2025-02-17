#include<bits/stdc++.h>
using namespace std;

#define bug(a) cout<< #a << " : " << a <<endl;
using ll = long long;

const int N = 1e5+7;
vector<int> g[N];
bool vis[N];
int col[N];

void dfs(int root){
    vis[root] = true;
    for(auto child : g[root]){
        if( !vis[child] ){
            col[child] = (col[root] ^ 1);
            dfs(child);
        }
    }
}

void solve( int cs ){

}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int testCase = 1, cs = 0;
    //cin >> testCase;

    while(testCase--){
        solve( ++cs );
    }

}

///     < BumbleBee >     ///
