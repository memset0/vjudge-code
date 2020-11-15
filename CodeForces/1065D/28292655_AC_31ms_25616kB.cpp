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
    while (c<'0'||c>'9') { if (c=='-') w=-1; c=getchar(); }
    while (c>='0'&&c<='9') X=X*10+c-'0',c=getchar();
    return X*w;
}

const int N=20;
const int M=30000;
const int L=10000;
const int dx_knight[8]={-1,1,2,2,1,-1,-2,-2};
const int dy_knight[8]={-2,-2,-1,1,2,2,1,-1};
const int dx_bishop[4]={-1,1,1,-1};
const int dy_bishop[4]={-1,-1,1,1};

struct Edge { int v,w,nxt; } e[2000010];
int head[M];

inline void addEdge(int u,int v,int w) {
    static int cnt=0;
    e[++cnt]=(Edge){v,w,head[u]},head[u]=cnt;
}

int n,sx,sy,tx,ty;
int a[N][N];
int id[3][N][N][N*N],tot=0;
int dis[M];

struct node { int u,d; };
bool operator <(node a,node b) { return a.d>b.d; }

inline void dijkstra() {
    priority_queue<node> Q; memset(dis,0x3f,sizeof(dis));
    for (re int i=0;i<3;++i) {
        int t=id[i][sx][sy][1];
        dis[t]=0; Q.push((node){t,0});
    }
    while (!Q.empty()) {
        node tp=Q.top(); Q.pop();
        int u=tp.u,d=tp.d;
        if (dis[u]!=d) continue;
        for (re int i=head[u];i;i=e[i].nxt) {
            int v=e[i].v,w=e[i].w;
            if (dis[u]+w<dis[v])
                dis[v]=dis[u]+w,Q.push((node){v,dis[v]});
        }
    }
}

int main() {
    n=read();
    for (re int i=1;i<=n;++i)
        for (re int j=1;j<=n;++j) {
            a[i][j]=read();
            if (a[i][j]==1) sx=i,sy=j;
            if (a[i][j]==n*n) tx=i,ty=j;
        }
    for (re int i=0;i<3;++i)
        for (re int j=1;j<=n;++j)
            for (re int k=1;k<=n;++k)
                for (re int l=1;l<=n*n;++l)
                    id[i][j][k][l]=++tot;
    for (re int i=1;i<=n;++i)
        for (re int j=1;j<=n;++j)
            for (re int k=1;k<=n*n;++k) {
                //走到了
                if (k+1==a[i][j]) {
                    for (re int l=0;l<3;++l)
                        addEdge(id[l][i][j][k],id[l][i][j][k+1],0);
                }
                //换棋子
                for (re int p=0;p<3;++p)
                    for (re int q=0;q<3;++q) {
                        if (p==q) continue;
                        addEdge(id[p][i][j][k],id[q][i][j][k],L+1);
                    }
                //车
                for (re int l=1;l<=n;++l) {
                    if (i!=l) addEdge(id[0][i][j][k],id[0][l][j][k],L);
                    if (j!=l) addEdge(id[0][i][j][k],id[0][i][l][k],L);
                }
                //马
                for (re int d=0;d<8;++d) {
                    int X=i+dx_knight[d],Y=j+dy_knight[d];
                    if (X<1||X>n||Y<1||Y>n) continue;
                    addEdge(id[1][i][j][k],id[1][X][Y][k],L);
                }
                //象
                for (re int d=0;d<4;++d)
                    for (re int l=1;l<=n;++l) {
                        int X=i+dx_bishop[d]*l,Y=j+dy_bishop[d]*l;
                        if (X<1||X>n||Y<1||Y>n) continue;
                        addEdge(id[2][i][j][k],id[2][X][Y][k],L);
                    }
            }
    dijkstra(); int ans=2e9;
    for (re int i=0;i<3;++i) {
        int now=dis[id[i][tx][ty][n*n]];
        ans=min(ans,now);
    }
    printf("%d %d\n",ans/L,ans%L);
    return 0;
}
//qwq