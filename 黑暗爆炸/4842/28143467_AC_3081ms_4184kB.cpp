// =================================
//   author: memset0
//   date: 2019.07.04 15:10:16
//   website: https://memset0.cn/
// =================================
#include <bits/stdc++.h>
#define ll long long
template<class T> inline void read(T &x){
  x=0;char c=getchar();bool f=0;
  while(!isdigit(c)) f^=c=='-',c=getchar();
  while(isdigit(c)) x=x*10+c-'0',c=getchar();if(f)x=-x;
}
template<class T> inline void print(T x){
  if(x<0)putchar('-'),x=-x;
  if(x>9)print(x/10);putchar('0'+x%10);
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=2e3+10,M=1e4+10,inf=1e9;
ll ans,dis[N];
int q[N*200],pre[N],inq[N];
int n,k,s,e,m,nod,t1,t2,a[N],b[N],id[N];
int tot=2,hed[N],nxt[M],to[M],val[M],cst[M];
inline void add_edge(int u,int v,int w,int c){
  nxt[tot]=hed[u],to[tot]=v,val[tot]=w,cst[tot]=c,hed[u]=tot++;
  nxt[tot]=hed[v],to[tot]=u,val[tot]=0,cst[tot]=-c,hed[v]=tot++;
}
bool spfa(){
  memset(pre,0,sizeof(pre));
  memset(dis,-63,sizeof(dis));
  int l=0,r=0,u;
  q[0]=s,dis[s]=0;
  while(l<=r){
    u=q[l++],inq[u]=0;
    for(int i=hed[u],v;v=to[i],i;i=nxt[i])
      if(val[i]&&dis[u]+cst[i]>dis[v]){
        dis[v]=dis[u]+cst[i],pre[v]=i;
        if(!inq[v])inq[q[++r]=v]=1;
      }
  }
  return pre[e];
}
int main(){
  read(n),read(k),read(t1),read(t2);
  m=(n-k+1)<<1|1,s=m+1,nod=e=m+2;
  for(int i=1;i<=n;i++)read(a[i]);
  for(int i=1;i<=n;i++)read(b[i]),ans+=b[i];
  for(int i=n,l,r;i>=1;i--){
    l=i<=k?1:(i-k)<<1|1;
    r=i>=n-k+1?m:i<<1|1;
    id[i]=tot,add_edge(l,r,1,a[i]-b[i]);
  }
  for(int i=1,l,r;i<=n-k+1;i++){
    l=i<<1,r=(i<<1)-1,add_edge(l,r,inf,0);
    l=i<<1,r=(i<<1)+1,add_edge(l,r,inf,0);
  }
  add_edge(s,1,t1,0),add_edge(m,e,k-t2,0);
  for(int i=2;i<=m-1;i++)
    (i&1)?add_edge(i,e,k-t1-t2,0):add_edge(s,i,k-t1-t2,0);
  while(spfa()){
    int flow=inf;
    for(int i=pre[e];i;i=pre[to[i^1]]) flow=std::min(flow,val[i]);
    for(int i=pre[e];i;i=pre[to[i^1]]) val[i]-=flow,val[i^1]+=flow,ans+=flow*cst[i];
  }
  print(ans,'\n');
  for(int i=1;i<=n;i++)putchar(val[id[i]]?'E':'S');
  putchar('\n');
}
