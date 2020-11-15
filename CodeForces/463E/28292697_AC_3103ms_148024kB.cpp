#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>
#include <set>
#define re register
using namespace std;

inline int read() {
    int X=0,w=1; char c=getchar();
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=100000+10;
const int V=2000000+10;

struct Edge { int v,nxt; } e[N<<1];
int head[N];

inline void addEdge(int u,int v) {
    static int cnt=0;
    e[++cnt]=(Edge){v,head[u]},head[u]=cnt;
}

int n,m;
int dep[N];
vector<int> divi[N];
pair<int,int> ans[N];
set<pair<int,int> > S[V];

inline void calc(int u,int w) {
    divi[u].clear();
    for (re int i=2;i*i<=w;++i) {
        if (w%i) continue;
        divi[u].push_back(i);
        while (w%i==0) w/=i;
    }
    if (w>1) divi[u].push_back(w);
}

inline void dfs(int u,int fa) {
    ans[u]=make_pair(-1,-1),dep[u]=dep[fa]+1;
    for (re int i:divi[u]) {
        if (S[i].size()) ans[u]=max(ans[u],*S[i].rbegin());
        S[i].insert(make_pair(dep[u],u));
    }
    for (re int i=head[u];i;i=e[i].nxt)
        if (e[i].v!=fa) dfs(e[i].v,u);
    for (re int i:divi[u])
        S[i].erase(make_pair(dep[u],u));
}

int main() {
    n=read(),m=read();
    for (re int i=1;i<=n;++i) calc(i,read());
    for (re int i=1;i<n;++i) {
        int u=read(),v=read();
        addEdge(u,v),addEdge(v,u);
    }
    dfs(1,0);
    for (re int i=1;i<=m;++i) {
        int op=read();
        if (op==1) printf("%d\n",ans[read()].second);
        else {
            int u=read(),w=read();
            calc(u,w),dfs(1,0);
        }
    }
    return 0;
}
//qwq