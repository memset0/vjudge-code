#include <cstdio>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <set>
#define int long long

int _T,n,K;
long long Dis[51][51];
int head[51],nxt[2000001],b[2000001],v[2000001],k,p[51],dis[51],S,T,h,t,q[1000001],ans;
long long dist[51][51],val[51][51],dis1[51],disn[51];
std::set<long long>set;
bool vis[51][51],did[51];
void getdis(int x,long long *dis){
    for(int i=1;i<=n;i++)dis[i]=1e16,did[i]=0;
    dis[x]=0;
    for(int i=1;i<=n;i++){
        int p=0;
        for(int j=1;j<=n;j++)
            if(!did[j]){
                if(!p)p=j;
                else if(dis[j]<dis[p])p=j;
            }
        did[p]=1;
        for(int j=1;j<=n;j++)
            dis[j]=std::min(dis[j],dis[p]+dist[p][j]);
    }
}
void brute(int K,long long stat){
    if(set.count(stat))return;
    for(int i=1;i<=50;i++)
        for(int j=1;j<=50;j++)
            if(vis[i][j])dist[i][j]=1e16;
            else dist[i][j]=Dis[i][j];
//    for(int k=1;k<=n;k++)
//        for(int i=1;i<=n;i++)
//            for(int j=1;j<=n;j++)
//                dist[i][j]=std::min(dist[i][j],dist[i][k]+dist[k][j]);
//    for(int i=1;i<=n;i++)dis1[i]=dist[1][i];
//    for(int i=1;i<=n;i++)disn[i]=dist[n][i];
    getdis(1,dis1);
    getdis(n,disn);
//    for(int i=1;i<=n;i++)printf("%lld ",dis1[i]);putchar('\n');
    int mn=dis1[n];
    ans=std::max(ans,mn);
    if(!K)return;
    std::vector<std::pair<int,int> >vec;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(!vis[i][j]&&(dis1[i]+Dis[i][j]+disn[j]==mn||dis1[j]+Dis[i][j]+disn[i]==mn)){
                vec.push_back(std::make_pair(i,j));
            }
    for(int i=0;i<vec.size();i++){
        vis[vec[i].first][vec[i].second]=vis[vec[i].second][vec[i].first]=1;
        brute(K-1,stat^val[vec[i].first][vec[i].second]);
        vis[vec[i].first][vec[i].second]=vis[vec[i].second][vec[i].first]=0;
    }
}
signed main(){
//    freopen("g.in","r",stdin);
    scanf("%lld",&_T);
    srand(19260817);
    for(int i=1;i<=50;i++)
        for(int j=1;j<=50;j++)
            for(int k=60;~k;--k)
                if(rand()%2)val[i][j]|=1ll<<(long long)k;
    for(int fd=1;fd<=_T;fd++){
        scanf("%lld%lld",&n,&K);
        ans=0;
        set.clear();
        for(int i=1,u,v,w;i<=((n*(n-1))>>1);i++)scanf("%lld%lld%lld",&u,&v,&w),Dis[u][v]=Dis[v][u]=w;
        brute(K,0);
        printf("%lld\n",ans);
    }
}