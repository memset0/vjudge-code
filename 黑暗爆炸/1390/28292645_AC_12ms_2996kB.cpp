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

const int N=100+10;

struct Point { int x,y; } a[N],b[N];
typedef Point Vector;
Vector operator -(Point a,Point b) { return (Vector){a.x-b.x,a.y-b.y}; }
inline int cross(Vector a,Vector b) { return a.x*b.y-a.y*b.x; }

int n,m;
Point s[N]; int top=0;
Point c[N]; int cnt=0;
int dis[N][N];

inline int cmp(Point u,Point v) {
    double A=atan2(u.y-a[1].y,u.x-a[1].x);
    double B=atan2(v.y-a[1].y,v.x-a[1].x);
    if (A!=B) return A<B;
    else return u.x<v.x;
}
inline void Graham() {
    int pos=1;
    for (re int i=2;i<=n;++i)
        if (a[i].y<a[pos].y||(a[i].y==a[pos].y&&a[i].x<a[pos].x)) pos=i;
    swap(a[1],a[pos]); sort(a+2,a+n+1,cmp);
    s[top=1]=a[1];
    for (re int i=2;i<=n;i++) {
        while (top>1&&cross(s[top]-s[top-1],a[i]-s[top-1])<=0) --top;
        s[++top]=a[i];
    }
    s[top+1]=s[1];
}

inline int inside(Point x,Point a,Point b,Point c) {
    int A=(cross(b-a,x-a)<0),B=(cross(c-b,x-b)<0),C=(cross(a-c,x-c)<0);
    return A==B&&B==C;
}

inline int inside(Point x) {
    if (cross(s[2]-s[1],x-s[1])<0) return 0;
    if (cross(s[top]-s[1],x-s[1])>0) return 0;
    int L=2,R=top;
    while (L<=R) {
        int mid=(L+R)>>1;
        if (cross(s[mid]-s[1],x-s[1])<0) R=mid-1;
        else L=mid+1;
    }
    return inside(x,s[1],s[R],s[R+1]);
}

int main() {
    n=read(),m=read();
    for (re int i=1;i<=n;++i) a[i].x=read(),a[i].y=read();
    for (re int i=1;i<=m;++i) b[i].x=read(),b[i].y=read();
    Graham();
    for (re int i=1;i<=m;++i)
        if (inside(b[i])) c[++cnt]=b[i];
    if (!cnt) { printf("%d\n",m*111); return 0; }
    memset(dis,0x3f,sizeof(dis));
    for (re int i=1;i<=n;++i)
        for (re int j=1;j<=n;++j) {   
            if (i==j) continue;
            int flag=1;
            for (re int k=1;k<=cnt;++k)
                if (cross(a[j]-a[i],c[k]-a[i])<0) { flag=0; break; }
            if (flag) dis[i][j]=1;
        }
    for (re int k=1;k<=n;++k)
        for (re int i=1;i<=n;++i)
            for (re int j=1;j<=n;++j)
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
    int ans=2e9;
    for (re int i=1;i<=n;++i) ans=min(ans,dis[i][i]);
    printf("%d\n",ans*20+(m-cnt)*111);
    return 0;
}
