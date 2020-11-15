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

const int N=100000+10;
const int mod=1e9+7;

int n,m,cnt,top;
int a[N],b[N],S[N];
pair<int,int> p[N];
int f[N];

inline int cmp(pair<int,int> a,pair<int,int> b) {
    if (a.first!=b.first) return a.first<b.first;
    else return a.second>b.second;
}

int c[N];
inline int lowbit(int x) { return x&-x; }
inline int query(int x) { int res=0;
    for (;x;x-=lowbit(x)) res=(res+c[x])%mod;
    return res;
}
inline void add(int x,int y) {
    for (;x<=top;x+=lowbit(x)) c[x]=(c[x]+y)%mod;
}

int main() {
    n=read(),m=read();
    for (re int i=1;i<=n;++i) a[i]=read();
    for (re int i=1;i<=m;++i) b[i]=read();
    for (re int i=1;i<=n;++i) {
        if (a[i]<=b[1]||a[i]>=b[m]) continue;
        int x=lower_bound(b+1,b+m+1,a[i])-b;
        if (b[x]==a[i]) continue;
        p[++cnt]=make_pair(a[i]-b[x-1],b[x]-a[i]);
        S[++top]=b[x]-a[i];
    }
    sort(S+1,S+top+1); top=unique(S+1,S+top+1)-S-1;
    for (re int i=1;i<=cnt;++i)
        p[i].second=lower_bound(S+1,S+top+1,p[i].second)-S;
    sort(p+1,p+cnt+1,cmp); cnt=unique(p+1,p+cnt+1)-p-1;
    f[0]=1;
    for (re int i=1;i<=cnt;++i)
        f[i]=query(p[i].second-1)+1,add(p[i].second,f[i]);
    int ans=0;
    for (re int i=0;i<=cnt;++i) ans=(ans+f[i])%mod;
    printf("%d\n",ans);
    return 0;
}
//qwq