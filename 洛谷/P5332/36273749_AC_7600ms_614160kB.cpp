// luogu-judger-enable-o2
// luogu-judger-enable-o2
// just for testing time limit.

// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e5+10;
int T,n,m,tot,s[maxn],vis[maxn],cnt,t[50010],ans[50010];
bitset<10000> b[maxn],f;
map<int,int> mp[50010];
basic_string<int> a[maxn],v[maxn];
int nod(int x,int y){
    if(mp[x].count(y))return mp[x][y];
    return mp[x][y]=tot++;
}
void dfs(int p){vis[p]=1;for(int i:a[p])if(!vis[i])dfs(i);s[++cnt]=p;}
void dfs1(int p){vis[p]=cnt;for(int i:a[p^1])if(!vis[i^1])dfs1(i^1);}
void work(int l,int r){
    for(int i=1;i<=cnt;i++)b[i].reset();
    f.reset();
    for(int i=l;i<=r;i++)b[vis[nod(i,T+1)*2]][i-l]=1;
    for(int i=cnt;i;i--)for(int j:v[i])b[i]|=b[j];
    for(int i=l;i<=r;i++)if(b[vis[nod(i,T+1)*2+1]][i-l])
        f[i-l]=1,t[i]=1;
    for(int i=1;i<=n;i++)
        ans[i]-=(b[vis[nod(i,T+1)*2+1]]|f).count();
}
int main(){
    scanf("%d%d%d",&T,&n,&m);
    for(int i=1;i<=m;i++){
        int op,t,x,y;scanf("%d%d%d%d",&op,&t,&x,&y);
        if(op==1)a[nod(x,t)*2+1]+=nod(y,t)*2,a[nod(y,t)*2+1]+=nod(x,t)*2;
        else a[nod(x,t)*2]+=nod(y,t+1)*2,a[nod(y,t+1)*2+1]+=nod(x,t)*2+1;
    }
    for(int i=1;i<=n;i++){
        nod(i,T+1);int ls=-1;
        for(auto&[_,v]:mp[i]){
            if(~ls)a[v*2+1]+=ls*2+1,a[ls*2]+=v*2;
            ls=v;
        }
    }
    for(int i=0;i<tot*2;i++)if(!vis[i])dfs(i);
    cnt=0;memset(vis,0,sizeof vis);
    for(int i=tot*2;i;i--)if(!vis[s[i]])++cnt,dfs1(s[i]);
    for(int i=0;i<tot*2;i++)for(int j:a[i])if(vis[i]!=vis[j])
        v[vis[i]]+=vis[j];
    for(int i=1;i<=n;i++)ans[i]=n-1;
    for(int i=1;i<=n;i+=1e4)
        work(i,min(i+9999,n));
    for(int i=1;i<=n;i++)printf("%d%c",t[i]?0:ans[i]," \n"[i==n]);
    return 0;
}