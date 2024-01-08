#include<bits/stdc++.h>
#define pi pair<int,int>
#define f first
#define s second
using namespace std;
const int N=2e5;
int T,n,m,p[N+10],ap[N+10],u,v,d[N+10],vis[N+10],la[N+10],prt[N+10];
pi tmp;
vector<int>e[N+10];
priority_queue<pi>pq;
void dfs(int x){
    if(vis[x])return;
    vis[x]=1;
    for(int i:e[x])dfs(i),la[x]=min(la[i],la[x]);
}
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;++i)vector<int>().swap(e[i]),d[i]=0,vis[i]=0,ap[i]=0,la[i]=n;
        while(!pq.empty())pq.pop();
        for(int i=1;i<=n;++i){
            scanf("%d",&p[i]);
            if(p[i])la[i]=p[i],ap[p[i]]=i;
        }
        for(int i=1;i<=m;++i){
            scanf("%d%d",&u,&v);
            e[u].push_back(v);
            ++d[v];
        }
        for(int i=1;i<=n;++i)if(!d[i]){
            dfs(i);
            if(!p[i])pq.push((pi){-la[i],i});
        }
        for(int i=1;i<=n;++i){
            if(!ap[i]){
                if(pq.empty()){
                    puts("-1");
                    goto Skip;
                }
                tmp=pq.top(),pq.pop(),tmp.f=-tmp.f;
                if(tmp.f<i){
                    puts("-1");
                    goto Skip;
                }
                ap[i]=tmp.s;
            }else tmp=(pi){0,ap[i]};
            for(int j:e[tmp.s]){
                --d[j];
                if(!p[j]&&!d[j])pq.push((pi){-la[j],j});
            }
        }
        for(int i=1;i<=n;++i)prt[ap[i]]=i;
        for(int i=1;i<=n;++i)printf("%d%c",prt[i]," \n"[i==n]);
        Skip:;
    }
    return 0;
}