// =================================
//   author: M_sea
//   website: http://m-sea-blog.com/
// =================================
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <queue>
#define re register
using namespace std;

inline int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') c=getchar();
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=80000+10;
const int mod=998244353;

inline int qpow(int a,int b) {
    int c=1;
    for (;b;b>>=1,a=1ll*a*a%mod)
        if (b&1) c=1ll*c*a%mod;
    return c;
}

int r[N];

inline void NTT(int* A,int lim,int op) {
    for (re int i=0;i<lim;++i) if (i<r[i]) swap(A[i],A[r[i]]);
    for (re int i=1;i<lim;i<<=1) {
        int rot=qpow(op==1?3:(mod+1)/3,(mod-1)/(i<<1));
        for (re int j=0;j<lim;j+=(i<<1)) {
            int w=1;
            for (re int k=0;k<i;++k,w=1ll*w*rot%mod) {
                int x=A[j+k],y=1ll*w*A[j+k+i]%mod;
                A[j+k]=(x+y)%mod,A[j+k+i]=(x-y+mod)%mod;
            }
        }
    }
    if (op==-1) {
        int inv=qpow(lim,mod-2);
        for (re int i=0;i<lim;++i) A[i]=1ll*A[i]*inv%mod;
    }
}

int fac[N],inv[N];
int F[N],G[N];

int main() {
    int n=read(),m=read()+1,x=read();
    
    fac[0]=1;
    for (re int i=1;i<=m;++i) fac[i]=1ll*fac[i-1]*i%mod;
    inv[m]=qpow(fac[m],mod-2);
    for (re int i=m;i;--i) inv[i-1]=1ll*inv[i]*i%mod;
    
    for (re int i=0;i<m;++i) F[i]=1ll*read()*inv[i]%mod;
    for (re int i=0;i<m;++i) G[i]=i&1?mod-inv[i]:inv[i];

    int lim=1,l=0; for (;lim<m+m;lim<<=1,++l);
    for (re int i=0;i<lim;++i) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
    NTT(F,lim,1),NTT(G,lim,1);
    for (re int i=0;i<lim;++i) F[i]=1ll*F[i]*G[i]%mod;
    NTT(F,lim,-1);

    int ans=0;
    for (re int i=0,t=1;i<m;++i) {
        ans=(ans+1ll*F[i]*t%mod)%mod;
        t=1ll*t*x%mod*(n-i)%mod;
    }
    printf("%d\n",(ans+mod)%mod);
    return 0;
}
