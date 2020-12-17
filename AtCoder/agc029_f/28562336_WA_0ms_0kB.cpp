#include<bits/stdc++.h>
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
  if(x<0)putchar('-'),x=-x;
  if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=1e5+10;
int n,id_node[N],id_set[N],match[N],used[N];
std::queue<int> q;
std::vector<int> a[N],e[N];
std::vector<std::pair<int,int>> ans;
inline void no_solution(){puts("-1"),exit(0);}
template<int N,int M> struct Dinic{
  int s/*起点*/,t/*点数&&终点*/,tot/*边数*/,cur[N],hed[N],dep[N],to[M<<1],val[M<<1],nxt[M<<1];
  Dinic(){tot=0,memset(hed,-1,sizeof(hed));}
  inline void add(int u,int v,int w){
    // printf("%d %d %d\n",u,v,w);
    nxt[tot]=hed[u],to[tot]=v,val[tot]=w,hed[u]=tot++;
    nxt[tot]=hed[v],to[tot]=u,val[tot]=0,hed[v]=tot++;
  }
  bool bfs(){
    static int u,l,r,q[N]; memset(dep+1,0,t<<2),l=r=dep[s]=1,q[1]=s;
    while(l<=r&&(u=q[l++]))for(int i=hed[u];~i;i=nxt[i])
      if(val[i]&&!dep[to[i]])dep[to[i]]=dep[u]+1,q[++r]=to[i];
    return dep[t];
  }
  int dfs(int u,int d){
    if(u==t)return d; int s=0;
    for(int &i=cur[u];~i;i=nxt[i])if(val[i]&&dep[to[i]]==dep[u]+1)
      if(int e=dfs(to[i],std::min(d-s,val[i]))){s+=e,val[i]-=e,val[i^1]+=e;if(s==d)return s;}
    return s?s:dep[s]=0;
  }
  int dinic(){int r=0;while(bfs())memcpy(cur+1,hed+1,t<<2),r+=dfs(s,1e9);return r;}
  int findout(int u){for(int i=hed[u];~i;i=nxt[i])if(!val[i]&&to[i]!=s&&to[i]!=t)return to[i];return -1;}
};
Dinic<N,N*2> flow;
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(n);
  for(int i=1,m;i<n;i++){
    read(m),a[i].resize(m);
    for(int j=0,x;j<m;j++)read(a[i][j]),e[a[i][j]].push_back(i);
  }
  for(int i=1;i<=n;i++)id_node[i]=++flow.t;
  for(int i=1;i<n;i++)id_set[i]=++flow.t;
  flow.s=++flow.t,++flow.t;
  for(int i=2;i<=n;i++){
    flow.add(flow.s,id_node[i],1);
  }
  for(int i=1;i<n;i++){
    flow.add(id_set[i],flow.t,1);
    for(int u:a[i])flow.add(id_node[u],id_set[i],1);
  }
  if(flow.dinic()!=n-1)no_solution();
  // for(int i=2;i<=n;i++)printf("%d > %d\n",i,flow.findout(i));
  for(int i=2;i<=n;i++)match[flow.findout(i)-n]=i;
  q.push(1);
  while(q.size()){
    int u=q.front(); q.pop();
    for(int v:e[u])if(!used[v]){
      ans.push_back(std::make_pair(u,match[v]));
      used[v]=1,q.push(match[v]);
    }
  }
  if(ans.size()!=n-1)no_solution();
  for(int i=0;i<n-1;i++)print(ans[i].first,' '),print(ans[i].second,'\n');
}