#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
#define re register
using namespace std;
typedef long long ll;

inline ll read() {
    ll X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=100000+10;

int n,l; ll c;
int a[N]; ll sum[N];

inline int check(int mid) {
    for (re int i=1,j=i+mid-1;j<=n;++i,++j) {
        ll now; int m=(i+j)>>1;
        if (mid&1) now=(sum[j]-sum[m])-(sum[m-1]-sum[i-1]);
        else now=(sum[j]-sum[m])-(sum[m]-sum[i-1]);
        if (now<=c) return 1;
    }
    return 0;
}

int main() {
    n=read(),l=read(),c=read();
    for (re int i=1;i<=n;++i) a[i]=read();
    for (re int i=1;i<=n;++i) sum[i]=sum[i-1]+a[i];
    int L=1,R=n;
    while (L<R) {
        int mid=(L+R+1)>>1;
        if (check(mid)) L=mid;
        else R=mid-1;
    }
    printf("%d\n",L);
    return 0;
}