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

const int N=100000+10;

struct Edge { int v,nxt; } e[N<<1];
int head[N];

inline void addEdge(int u,int v) {
    static int cnt=0;
    e[++cnt]=(Edge){v,head[u]},head[u]=cnt;
}

int n,m,block,c[N];
int dfn[N],low[N],rl[N],tim=0;
int num[N],sum[N],ans[N];
struct query { int l,r,k,id,bl; } q[N];
inline bool cmp(query a,query b) {
    if (a.bl!=b.bl) return a.l<b.l;
    else return (a.bl&1)?(a.r<b.r):(a.r>b.r);
}

inline void dfs(int u,int fa) {
    dfn[u]=++tim,rl[tim]=u;
    for (re int i=head[u];i;i=e[i].nxt)
        if (e[i].v!=fa) dfs(e[i].v,u);
    low[u]=tim;
}


inline void add(int i) { ++num[c[i]],++sum[num[c[i]]]; }
inline void del(int i) { --sum[num[c[i]]],--num[c[i]]; }

inline void solve() {
    sort(q+1,q+m+1,cmp);
    int l=1,r=0;
    for (re int i=1;i<=m;++i) {
        while (l<q[i].l) del(rl[l]),++l;
        while (l>q[i].l) --l,add(rl[l]);
        while (r<q[i].r) ++r,add(rl[r]);
        while (r>q[i].r) del(rl[r]),--r;
        ans[q[i].id]=sum[q[i].k];
    }
}

int main() {
    n=read(),m=read(),block=sqrt(n);
    for (re int i=1;i<=n;++i) c[i]=read();
    for (re int i=1;i<n;++i) {
        int u=read(),v=read();
        addEdge(u,v),addEdge(v,u);
    }
    dfs(1,0);
    for (re int i=1;i<=m;++i) {
        int u=read(),k=read();
        q[i].l=dfn[u],q[i].r=low[u],q[i].k=k;
        q[i].id=i,q[i].bl=(q[i].l-1)/block;
    }
    solve();
    for (re int i=1;i<=m;++i) printf("%d\n",ans[i]);
    return 0;
}

// dafdfads