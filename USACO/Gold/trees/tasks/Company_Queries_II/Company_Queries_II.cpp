#include<bits/stdc++.h>

using namespace std ;

const int Size = 2e5 + 1 ;

int n , q , src , dest  , qx , qy;
int levels[Size] ;
int parents[Size][19] ;

vector<int>adj[Size] ;

void dfs (int node , int par){

    levels[node] = levels[par] + 1 ;
    parents[node][0] = par ;

    for(int i = 1 ; i <= 18 ; i ++ ){
        parents[node][i] = parents[parents[node][i - 1]][i - 1] ;
    }

    for(int next : adj[node]){
        dfs(next , node) ;
    }

    return ;
}

int lca(int x , int y){

    if(levels[x] < levels[y])swap(x , y) ;

    int diff_level = (levels[x] - levels[y]) ;

    for(int i = 18 ; i >= 0 ; i -- ){

        int stride = (1 << i) ;

        if( stride <= diff_level ){
            x = parents[x][i] ;
            diff_level -= stride ;
        }
    }

    if(x == y) return x ;

    for(int i = 18 ; i >= 0 ; i -- ){

        if(parents[x][i] != parents[y][i]){
            x = parents[x][i] ;
            y = parents[y][i] ;
        }

        // cout << x << ' ' << y << '\n' ;
    }

    x = parents[x][0] ;
    
    return x ;

}

int main(){

    ios_base :: sync_with_stdio(0) , cin.tie(0) ;

    cin >> n >> q ;

    for(int i = 2 ; i <= n ; i ++ ){
        cin >> src ;
        adj[src].push_back(i) ;
    }

    dfs(1 , 0) ;

    while(q -- ){
        cin >> qx >> qy ;
        cout << lca(qx , qy) << '\n' ;
    }
    // for(int i = 1 ; i <= n ; i ++ ){
    //     cout << "Node = " << i << ' ' << "level = " << levels[i] << '\n' ;
    //     for(int j = 0 ; j <= 18 ; j ++ ){
    //         cout << parents[i][j] << ' ' ;
    //     }
    //     cout << '\n' ;
    // }

    return 0 ;
}