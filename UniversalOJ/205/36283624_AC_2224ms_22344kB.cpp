#include <bits/stdc++.h>
#define re register
using namespace std;
typedef long long ll;

inline int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=600000+10;

int n,m,tot=0;
ll ans=0;
int fa[N],c[N],deg[N],rt[N];

struct node { int ls,rs,dis; ll x; } t[N];
inline int merge(int x,int y) {
    if (!x||!y) return x+y;
    if (t[x].x<t[y].x) swap(x,y);
    t[x].rs=merge(t[x].rs,y);
    if (t[t[x].ls].dis<t[t[x].rs].dis) swap(t[x].ls,t[x].rs);
    if (!t[x].rs) t[x].dis=0;
    else t[x].dis=t[t[x].rs].dis+1;
    return x;
}
inline int pop(int x) { return merge(t[x].ls,t[x].rs); }

int main() {
    n=read(),m=read();
    for (re int i=2;i<=n+m;++i) fa[i]=read(),c[i]=read();
    for (re int i=2;i<=n+m;++i) ++deg[fa[i]],ans+=c[i];
    for (re int i=n+m;i>1;--i) {
        ll l=0,r=0;
        if (i<=n) {
            while (--deg[i]) rt[i]=pop(rt[i]);
            r=t[rt[i]].x,rt[i]=pop(rt[i]);
            l=t[rt[i]].x,rt[i]=pop(rt[i]);
        }
        t[++tot].x=l+c[i],t[++tot].x=r+c[i];
        rt[i]=merge(rt[i],merge(tot-1,tot));
        rt[fa[i]]=merge(rt[fa[i]],rt[i]);
    }
    while (deg[1]--) rt[1]=pop(rt[1]);
    while (rt[1]) ans-=t[rt[1]].x,rt[1]=pop(rt[1]);
    printf("%lld\n",ans);
    return 0;
}
