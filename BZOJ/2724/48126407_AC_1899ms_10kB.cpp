// ===================================
//   author: M_sea
//   website: http://m-sea-blog.com/
// ===================================
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#define re register
using namespace std;

inline int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=40000+10,SQ=200+10;

int n,m,a[N],S[N];
int B,C,L[SQ],R[SQ],bl[N],s[SQ][N],f[SQ][SQ];
int o[N];

int main() {
    n=read(),m=read(); B=sqrt(n),C=n/B+(n%B!=0);
    for (re int i=1;i<=C;++i) L[i]=R[i-1]+1,R[i]=min(i*B,n);
    for (re int i=1;i<=n;++i) bl[i]=(i-1)/B+1;
    for (re int i=1;i<=n;++i) S[i]=a[i]=read();
    sort(S+1,S+n+1); int c=unique(S+1,S+n+1)-S-1;
    for (re int i=1;i<=n;++i) a[i]=lower_bound(S+1,S+c+1,a[i])-S;
    for (re int i=1;i<=C;++i) {
        for (re int j=L[i];j<=R[i];++j) ++s[i][a[j]];
        for (re int j=1;j<=c;++j) s[i][j]+=s[i-1][j];
    }
    for (re int i=1;i<=C;++i)
        for (re int j=i;j<=C;++j) {
            f[i][j]=f[i][j-1];
            for (re int k=L[j];k<=R[j];++k) {
                int cr=s[j][f[i][j]]-s[i-1][f[i][j]];
                int ca=s[j][a[k]]-s[i-1][a[k]];
                if (ca>cr||(ca==cr&&a[k]<f[i][j])) f[i][j]=a[k];
            }
        }
    int lastans=0;
    while (m--) {
        int l=(read()+lastans-1)%n+1,r=(read()+lastans-1)%n+1;
        if (l>r) swap(l,r);
        if (bl[r]-bl[l]<=1) {
            for (re int i=l;i<=r;++i) ++o[a[i]];
            int res=0;
            for (re int i=l;i<=r;++i)
                if (o[a[i]]>o[res]||(o[a[i]]==o[res]&&a[i]<res)) res=a[i];
            printf("%d\n",lastans=S[res]);
            for (re int i=l;i<=r;++i) --o[a[i]];
        } else {
            for (re int i=l;i<=R[bl[l]];++i) ++o[a[i]];
            for (re int i=L[bl[r]];i<=r;++i) ++o[a[i]];
            int res=f[bl[l]+1][bl[r]-1];
            for (re int i=l;i<=R[bl[l]];++i) {
                int cr=o[res]+s[bl[r]-1][res]-s[bl[l]][res];
                int ca=o[a[i]]+s[bl[r]-1][a[i]]-s[bl[l]][a[i]];
                if (ca>cr||(ca==cr&&a[i]<res)) res=a[i];
            }
            for (re int i=L[bl[r]];i<=r;++i) {
                int cr=o[res]+s[bl[r]-1][res]-s[bl[l]][res];
                int ca=o[a[i]]+s[bl[r]-1][a[i]]-s[bl[l]][a[i]];
                if (ca>cr||(ca==cr&&a[i]<res)) res=a[i];
            }
            printf("%d\n",lastans=S[res]);
            for (re int i=l;i<=R[bl[l]];++i) --o[a[i]];
            for (re int i=L[bl[r]];i<=r;++i) --o[a[i]];
        }
    }
    return 0;
}
