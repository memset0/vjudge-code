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

const int N=2000000+10;

struct Edge { int v,nxt; } e[N<<1];
int head[N],cnt=0;

inline void addEdge(int u,int v) {
    e[++cnt]=(Edge){v,head[u]},head[u]=cnt;
}

int n,deg[N];
char str[N];

int main() {
    int T=read();
    while (T--) {
        memset(head,0,sizeof(int)*(n+1)),cnt=0;
        memset(deg,0,sizeof(int)*(n+1));
        
        n=read();
        for (re int i=1;i<n;++i) {
            int u=read(),v=read();
            addEdge(u,v),addEdge(v,u);
            ++deg[u],++deg[v];
        }
        scanf("%s",str+1);
        
        if (n<3) { puts("Draw"); continue; }
        if (n==3) {
            int sum=0;
            for (re int i=1;i<=3;++i) sum+=(str[i]=='W');
            puts(sum>=2?"White":"Draw");
            continue;
        }
        
        for (re int i=1;i<=n;++i) {
            if (str[i]!='W') continue;
            ++n,head[n]=0;
            addEdge(i,n),addEdge(n,i);
            ++deg[i],deg[n]=3;
        }
        
        int flag=0,s=0;
        for (re int i=1;i<=n;++i) {
            if (deg[i]>3) { flag=1; break; }
            if (deg[i]==3) {
                int sum=0;
                for (re int j=head[i];j;j=e[j].nxt)
                    if (deg[e[j].v]>=2) ++sum;
                if (sum>=2) { flag=1; break; }
                ++s;
            }
        }
        if (s==2&&(n&1)) flag=1;
        puts(flag?"White":"Draw");
    }
    return 0;
}