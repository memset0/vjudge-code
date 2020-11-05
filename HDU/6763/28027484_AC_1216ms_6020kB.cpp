#include <cstdio>
#include <algorithm>

struct point{
    int ord,b;
}num[200001];
int t,n,m,head[100001],nxt[400001],b[400001],k,f[100001],cnt;
bool vis[100001];
void push(int s,int t){
    nxt[++k]=head[s];
    head[s]=k;
    b[k]=t;
}
bool cmp(point a,point b){
    return a.b<b.b;
}
int find(int x){
    return f[x]?f[x]=find(f[x]):x;
}
int main(){
    scanf("%d",&t);
    for(int fd=1;fd<=t;fd++){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)scanf("%d",&num[i].b),num[i].ord=i,f[i]=0,vis[i]=0;
        std::sort(num+1,num+n+1,cmp);
        for(int i=1;i<=n;i++)head[i]=0;
        k=0;
        for(int i=1,u,v;i<=m;i++)scanf("%d%d",&u,&v),push(u,v),push(v,u);
        cnt=0;
        long long ans=0;
        for(int i=n;i;i--){
            int u=num[i].ord;
            ++cnt;
            vis[u]=1;
            for(int j=head[u];j;j=nxt[j])
                if(vis[b[j]]){
                    int g=find(b[j]);
                    if(g!=find(u)){
                        f[g]=find(u);
                        cnt--;
                    }
                }
//            printf("%d %d %d\n",i,cnt,num[i].b-num[i-1].b);
            ans+=1ll*(num[i].b-num[i-1].b)*cnt;
        }
        printf("%lld\n",ans);
    }
}