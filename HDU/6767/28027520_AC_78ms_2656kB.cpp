#include <algorithm>
#include <cstring>
#include <cstdio>
#include <map>
#define int long long

long long a[51],B[51],c[51];
std::map<int,int>map;
int _T,n,m,head[100001],nxt[300001],b[300001],v[300001],flow[300001],q[300001],h,t,S,T,dis[100001],pre[100001],k=1,v2[300001];
bool inq[100001];
long long cost[300001];
void push(int s,int t,int val,long long c){
    nxt[++k]=head[s];
    head[s]=k;
    b[k]=t;
    v[k]=val;
    v2[k]=c;
}
void link(int s,int t,int val,long long c){
//    printf("%d %d\n",s,t);
    push(s,t,val,c);
    push(t,s,0,-c);
}
bool spfa(){
    h=t=0;
    for(int i=S;i<=T;i++)dis[i]=1e18;
    for(int i=S;i<=T;i++)inq[i]=0;
    q[++t]=S;
    inq[S]=1;
    dis[S]=0;
    flow[S]=0x7f7f7f7f;
    while(h<t){
        h++;
        inq[q[h]]=0;
        for(int i=head[q[h]];i;i=nxt[i])
            if(v[i]&&dis[b[i]]>dis[q[h]]+v2[i]){
                dis[b[i]]=dis[q[h]]+v2[i];
                flow[b[i]]=std::min(flow[q[h]],v[i]);
                pre[b[i]]=i;
                if(!inq[b[i]])q[++t]=b[i],inq[b[i]]=1;
            }
    }
//    for(int i=S;i<=T;i++)printf("%d %lld %d\n",i,dis[i],b[pre[i]^1]);
    return dis[T]!=1e18;
}
long long f(int x,long long j){
    return 1ll*a[x]*j*j+1ll*B[x]*j+c[x];
}
signed main(){
    scanf("%lld",&_T);
    for(int fd=1;fd<=_T;fd++){
        scanf("%lld%lld",&n,&m);
        T=n;
        map.clear();
        for(int i=1;i<=n;i++){
            scanf("%lld%lld%lld",a+i,B+i,c+i);
            long long mn=std::min(std::max(-(B[i]/(a[i]<<1)),1ll),m);
            for(int j=-n;j<=n;j++)
                if(mn+j>=1&&mn+j<=m){
                    if(!map.count(mn+j))map[mn+j]=++T;
                    link(i,map[mn+j],1,f(i,mn+j));
                }
        }
        ++T;
        for(int i=1;i<=n;i++){
            link(S,i,1,0);
        }
        for(int i=n+1;i<T;i++)link(i,T,1,0);
        int cost=0;
        bool cando=0;
        while(spfa()){
            int u=T;
            while(u!=S){
//                printf("%d\n",u);
                v[pre[u]]-=flow[T];
                v[pre[u]^1]+=flow[T];
                u=b[pre[u]^1];
            }
            cost+=dis[T]*flow[T];
            if(cando)putchar(' ');
            printf("%lld",cost);
            cando=1;
        }
        putchar('\n');
        for(int i=S;i<=T;i++)head[i]=0;
        k=1;
    }
}