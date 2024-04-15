#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
using namespace std ;

int N , B , S , R ;
struct Path{ int pre , to , len ; } ;
struct dijk_Data{
    int dis , id ;
    dijk_Data( int _ , int __ ):dis(_) , id(__) {} ;
    bool operator < ( const dijk_Data &A ) const {
        return dis > A.dis ;
    }
} ;
struct Data{
    int k , ed ;
    long long val ;
} dp[50005] , que[50005] ;
struct Graph{
    int head[50005] , tp , dist[5005] ;
    Path p[500005] ;
    void In( int t1 , int t2 , int t3 ){
        p[++tp] = ( Path ){ head[t1] , t2 , t3 } ; head[t1] = tp ;
    }

    bool vis[5005] ;
    priority_queue<dijk_Data> que ;
    void dijk(){
        memset( dist , 0x3f , sizeof( dist ) ) ;
        dist[B+1] = 0 , que.push( dijk_Data( 0 , B + 1 ) ) ;
        while( !que.empty() ){
            int u = que.top().id ; que.pop() ;
            if( vis[u] ) continue ; vis[u] = true ;
            for( int i = head[u] ; i ; i = p[i].pre ){
                int v = p[i].to ;
                if( dist[v] > dist[u] + p[i].len ){
                    dist[v] = dist[u] + p[i].len ;
                    que.push( dijk_Data( dist[v] , v ) ) ;
                }
            }
        }
    }
} G1 , G2 ;

long long sum[5005] ;
void preWork(){
    G1.dijk() , G2.dijk() ;
    for( int i = 1 ; i <= B ; i ++ ) sum[i] = G1.dist[i] + G2.dist[i] ;
    sort( sum + 1 , sum + B + 1 , greater<long long>() ) ;
    for( int i = 1 ; i <= B ; i ++ ) sum[i] += sum[i-1] ;
}

int fr , ba ;
long long Val( Data x , int now ){
    return x.val + ( sum[now] - sum[x.ed] ) * ( now - x.ed - 1 ) ;
}

int better( Data x , Data y ){
    int lf = x.ed , rg = B , rt = B + 1 ;
    while( lf <= rg ){
        int mid = ( lf + rg ) >> 1 ;
        long long v1 = Val( x , mid ) , v2 = Val( y , mid ) ;
        if( v1 < v2 || ( v1 == v2 && x.k < y.k ) ) rg = mid - 1 , rt = mid ;
        else lf = mid + 1 ;
    } return rt ;
}

void Push( Data x ){
    while( ba > fr ){
        int t1 = better( que[ba] , que[ba-1] ) , t2 = better( x , que[ba] ) ;
        if( t1 > t2 || ( t1 == t2 && que[ba].k >= x.k ) ) ba -- ;
        else break ;
    } que[++ba] = x ;
}

void Pop( int i ){
    while( ba > fr ){
        long long v1 = Val( que[fr] , i ) , v2 = Val( que[fr+1] , i ) ;
        if( v1 > v2 || ( v1 == v2 && que[fr].k > que[fr+1].k ) ) fr ++ ;
        else break ;
    }
}

Data calc( long long mid ){
    fr = 1 , ba = 0 , que[++ba] = ( Data ){ 0 , 0 , 0 } ;
    for( int i = 1 ; i <= B ; i ++ ){
        Pop( i ) ;
        dp[i] = ( Data ){ que[fr].k + 1 , i , Val( que[fr] , i ) + mid } ;
        Push( dp[i] ) ;
    } return dp[B] ;
}

void solve(){
    long long lf = 0 , rg = sum[B] * B , ans ;
    while( lf <= rg ){
        long long mid = ( lf + rg ) >> 1 ;
        Data res = calc( mid ) ;
        if( res.k == S )
            return ( void )printf( "%lld\n" , res.val - mid * S ) ;
        if( res.k > S ) lf = mid + 1 ;
        else ans = mid ,rg = mid - 1 ;
    } printf( "%lld\n" , calc( ans ).val - ans * S ) ;
}

int main(){
    scanf( "%d%d%d%d" , &N , &B , &S , &R ) ;
    for( int i = 1 , u , v , l ; i <= R ; i ++ ){
        scanf( "%d%d%d" , &u , &v , &l ) ;
        G1.In( u , v , l ) , G2.In( v , u , l ) ;
    } preWork() ; solve() ;
}

