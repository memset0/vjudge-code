#include<bits/stdc++.h>
using namespace std;
const int N=3e5+10,mod=1e9+7;
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
struct Edge{
  int v,nxt;
};
Edge edge[N*2];
int fir[N],ss,n;
void addedge(int u,int v){
  ss++;
  edge[ss].v=v,edge[ss].nxt=fir[u];
  fir[u]=ss;
  ss++;
  edge[ss].v=u,edge[ss].nxt=fir[v];
  fir[v]=ss;
}
int dep[N],son[N][2],siz[N],ed[N],len[N],ok[N],sn[N][20],f[N],vis[N];
void dfs(int u,int fa){
  dep[u]=dep[fa]+1;
  sn[fa][0]=u;
  int cnt=0;
  for(int i=fir[u];i!=0;i=edge[i].nxt){
    int v=edge[i].v;
    if(v!=fa){
      if(cnt==2){
        cout<<"0\n";
        exit(0);
      }
      son[u][cnt++]=v;
      dfs(v,u);
    }
  }
  siz[u]=cnt;
  if(cnt==0){
    ok[u]=1,len[u]=1,ed[u]=u;
  }
  if(cnt==1){
    int v=son[u][0];
    ok[u]=ok[v],ed[u]=ed[v];
    if(ok[u]) len[u]=len[v]+1;
  }
  if(cnt==2){
    ok[u]=0,len[u]=0;
    ed[u]=u;
  }
}
int jump(int u,int dep){
  for(int i=19;i>=0;i--){
    if(dep>=(1<<i)){
      dep-=(1<<i);
      u=sn[u][i];
    }
  }
  return u;
}
int dfs2(int u);
int solve(int x,int y){
  if(siz[y]==0) {
		return dfs2(x);
	}
  if(siz[y]==2) {
		return 0;
	}
  y=son[y][0];
  if(ok[x]&&ok[y]&&len[x]==len[y]) {
		return 1;
	}
  int ans=0;
  if(ok[x]){
    if(dep[ed[y]]-dep[y]>=len[x]) {
			ans=add(ans,dfs2(jump(y,len[x])));
		}
  }
  if(ok[y]){
    if(dep[ed[x]]-dep[x]>=len[y]){
			 ans=add(ans,dfs2(jump(x,len[y])));
		}
  }
  return ans;
}
int solve2(int x,int y){
  if(ok[x]&&ok[y]&&len[x]==len[y]) {
		return 1;
	}
  int fuck=0;
  if(ok[x]){
    if(dep[ed[y]]-dep[y]>=len[x]) {
			fuck=add(fuck,dfs2(jump(y,len[x])));
		}
  }
  if(ok[y]){
    if(dep[ed[x]]-dep[x]>=len[y]) {
			fuck=add(fuck,dfs2(jump(x,len[y])));
		}
  }
  return fuck;
}
int dfs2(int u){
  if(f[u]||vis[u]) {
		return f[u];
	}
  if(!siz[u]) {
		return f[u]=1;
	}
  vis[u]=1;
  if(siz[u]==1){
    int v=son[u][0];
    if(siz[v]==0) f[u]=1;
    if(siz[v]==1) f[u]=dfs2(son[v][0]);
    f[u]=add(f[u],dfs2(v));
    if(ok[u]&&len[u]>=4&&len[u]%2==0) f[u]=add(f[u],1);
    if(!ok[u]){
      int x=ed[u];
      int A=son[x][0],B=son[x][1];
      int L=dep[x]-dep[u]+1;
      if(ok[A]&&len[A]==L) f[u]=add(f[u],dfs2(B));
      if(ok[B]&&len[B]==L) f[u]=add(f[u],dfs2(A));
      if(ok[A]&&len[A]==L-2) f[u]=add(f[u],dfs2(B));
      if(ok[B]&&len[B]==L-2) f[u]=add(f[u],dfs2(A));
      if(siz[B]==2){
        int C=son[B][0],D=son[B][1];
        if(ok[C]&&len[C]==L-1) f[u]=add(f[u],solve2(A,D));
        if(ok[D]&&len[D]==L-1) f[u]=add(f[u],solve2(A,C));
      }
      if(siz[A]==2){
        swap(A,B);
        int C=son[B][0],D=son[B][1];
        if(ok[C]&&len[C]==L-1) f[u]=add(f[u],solve2(A,D));
        if(ok[D]&&len[D]==L-1) f[u]=add(f[u],solve2(A,C));
        swap(A,B);
      }
    }
  }
  if(siz[u]==2){
    int x=son[u][0],y=son[u][1];
    f[u]=add(solve(x,y),solve(y,x));
  }
  return f[u];
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(int u,v,i=1;i<n;i++){
		cin>>u>>v;
    addedge(u,v);
  }
  dfs(1,0);
  for(int i=1;i<=19;i++){
    for(int j=1;j<=n;j++){
      sn[j][i]=sn[sn[j][i-1]][i-1];
    }
  }
  cout<<dfs2(1)<<endl;
  return 0;
}
//dasfiojadsfioadsfiasdhjahjdsfjikhadshkfadsghjkfghyujkadsghyuk