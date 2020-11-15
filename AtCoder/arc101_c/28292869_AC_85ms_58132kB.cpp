// ===================================
//   author: M_sea
//   website: http://m-sea-blog.com/
// ===================================
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#define re register
using namespace std;

inline int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=5000+10;
const int mod=1e9+7;

struct edge { int v,nxt; } e[N<<1];
int head[N];

inline void addEdge(int u,int v) {
    static int e_cnt=0;
    e[++e_cnt]=(edge){v,head[u]},head[u]=e_cnt;
}

int n,sz[N];
int f[N][N],g[N],tmp[N];

inline void dfs(int u,int fa) {
    sz[u]=f[u][1]=1;
    for (re int i=head[u];i;i=e[i].nxt) {
        int v=e[i].v; if (v==fa) continue;
        dfs(v,u);
        for (re int j=1;j<=sz[u]+sz[v];++j) tmp[j]=0;
        for (re int j=1;j<=sz[u];++j)
            for (re int k=0;k<=sz[v];++k)
                tmp[j+k]=(tmp[j+k]+1ll*f[u][j]*f[v][k])%mod;
        sz[u]+=sz[v];
        for (re int j=1;j<=sz[u];++j) f[u][j]=tmp[j];
    }
    for (re int i=2;i<=sz[u];i+=2)
        f[u][0]=(f[u][0]-1ll*f[u][i]*g[i]%mod+mod)%mod;
}

int main() {
    n=read();
    for (re int i=1;i<n;++i) {
        int u=read(),v=read();
        addEdge(u,v),addEdge(v,u);
    }
    g[0]=1;
    for (re int i=2;i<=n;i+=2) g[i]=1ll*g[i-2]*(i-1)%mod;
    dfs(1,0); printf("%d\n",mod-f[1][0]);
    return 0;
}
//qwq