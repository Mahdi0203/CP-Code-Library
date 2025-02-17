#include<bits/stdc++.h>
using namespace std;

#define bug(a) cout<< #a << " : " << a <<endl;
using ll = long long;

const int N = 1e5+7;
vector<int> g[N];
bool cycle;
int col[N], par[N];

void dfs(int root){
    col[root] = 1;
    for(auto child : g[root]){
        if( !col[child] ){
            par[child] = root;
            dfs(child);
        }
        else if( col[child] == 1 ){
            cycle = true;       // can track the cycle using parent array.
        }
    }
    col[root] = 2;
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
