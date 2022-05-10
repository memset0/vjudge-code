#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,m,nod,top,tim,cnt,col[N],stk[N],dfn[N],low[N];
bool ins[N];
vector<int> G[N],vec[N];
set<pair<int,int>> S[N];
vector<pair<int,int>> C[N];
union Node{
  struct{int p[2],ch[2];};
  struct{int u,v,l,r;};
}e[N];
void tarjan(int u,int fa){
  dfn[u]=low[u]=++tim,stk[++top]=u,ins[u]=true;
  for(int v:G[u])if(v!=fa){
    if(!dfn[v]){
      tarjan(v,u);
      low[u]=min(low[u],low[v]);
    }else if(ins[v]){
      low[u]=min(low[u],dfn[v]);
    }
  }
  if(dfn[u]==low[u]){
    col[u]=++cnt;
    do{
      col[stk[top]]=cnt;
      ins[stk[top]]=false;
      vec[cnt].push_back(stk[top]);
    }while(stk[top--]);
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m,nod=m;
  for(int i=1;i<=m;i++){
    cin>>e[i].u>>e[i].v;
    G[e[i].u].push_back(e[i].v);
    G[e[i].v].push_back(e[i].u);
  }
  for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i,-1);
  
}
