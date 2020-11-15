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

int n,m;
int d[N],a[N];
int lst[N],mark[N],id[N];

inline int cmp(int a,int b) { return lst[a]<lst[b]; }

inline int check(int t) {
    memset(lst,0,sizeof(lst)),memset(mark,0,sizeof(mark));
    for (re int i=1;i<=t;++i) lst[d[i]]=i;
    for (re int i=1;i<=m;++i) if (!lst[i]) return 0;
    for (re int i=1;i<=m;++i) mark[lst[i]]=1;
    for (re int i=1;i<=m;++i) id[i]=i;
    sort(id+1,id+m+1,cmp);
    for (re int i=1,j=0;i<=m;++i) {
        if (j+a[id[i]]>=lst[id[i]]) return 0;
        int cnt=a[id[i]];
        while (j<=t&&cnt) {
            ++j; if (j>t) return 0;
            if (!mark[j]) --cnt;
        }
    }
    return 1;
}

int main() {
    n=read(),m=read();
    for (re int i=1;i<=n;++i) d[i]=read();
    for (re int i=1;i<=m;++i) a[i]=read();
    if (!check(n)) { puts("-1"); return 0; }
    int L=1,R=n;
    while (L<R) {
        int mid=(L+R)>>1;
        if (check(mid)) R=mid;
        else L=mid+1;
    }
    printf("%d\n",R);
    return 0;
}