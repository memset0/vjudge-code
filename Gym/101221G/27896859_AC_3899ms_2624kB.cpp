#include<bits/stdc++.h>
using namespace std;
const int N=405;
struct edge{
  int v,nxt;
}c[N*N];
int hed[N],edg;
inline void addedge(int u,int v){
  c[++edg]=(edge){v,hed[u]};
  hed[u]=edg;
}
int dfn[N],low[N],id,n;
int st[N],top,bel[N],col;
bool flag;
void tarjan(int x){
  dfn[x]=low[x]=++id;
  st[++top]=x;
  for(int i=hed[x];i&&!flag;i=c[i].nxt){
    int v=c[i].v;
    if(!dfn[v]){
			tarjan(v),low[x]=min(low[x],low[v]);
    }else if(!bel[v]){
			low[x]=min(low[x],dfn[v]);
		}
  }
  if(flag) return;
  if(dfn[x]==low[x]){
    bel[x]=++col,flag|=bel[x]==bel[x+(x<=n?n:-n)];
    while(st[top]!=x){
      int tmp=st[top--];
      bel[tmp]=col;
      flag|=bel[tmp]==bel[tmp+(tmp<=n?n:-n)];
    }
    --top;
  }
}
int t[N*N],a[N][N];
bool check(int v1,int v2){
  memset(dfn,0,(n+n+3)<<2),memset(low,0,(n+n+3)<<2),memset(bel,0,(n+n+3)<<2),memset(hed,0,(n+n+3)<<2);
  top=id=col=edg=0;
  for(int i=1;i<=n;++i)for(int j=i+1;j<=n;++j)if(a[i][j]>v1)addedge(i,j+n),addedge(j,i+n);
  for(int i=1;i<=n;++i)for(int j=i+1;j<=n;++j)if(a[i][j]>v2)addedge(i+n,j),addedge(j+n,i);
  flag=false;
  for(int i=1;i<=n+n;++i)if(!dfn[i])tarjan(i);
  return flag^1;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  int pos=1,ans=0;t[1]=0;
  for(int x,i=1;i<=n;++i)
    for(int j=i+1;j<=n;++j){
      cin>>x,t[++pos]=x;
      ans=max(ans,a[i][j]=x);
    }
  sort(t+1,t+pos+1),pos=unique(t+1,t+pos+1)-t-1,t[++pos]=1e9;
  int cur=pos;
  for(int i=1;i<=pos;++i){
    if(t[i]+t[i]>=ans)continue;
    while(cur>=i&&check(t[i],t[cur-1])) --cur;
    ans=min(ans,t[i]+t[cur]);
    if(cur<i)break;
  }
  cout<<ans<<endl;
}