#include<bits/stdc++.h>
const int N=30;
int n,m,tim,top,mrk[N],p[128],deg[N],ins[N],col[N],dfn[N],low[N],stk[N];
long long fac=1,dp[1<<20];
std::vector<int> G[N],E[N];
inline int get(){int c=getchar();while(!isalpha(c)&&c!='1')c=getchar();return c-'a'+1;}
void tarjan(int u){
  dfn[u]=low[u]=++tim,stk[++top]=u,ins[u]=1;
  for(int v:G[u])low[u]=std::min(low[u],dfn[v]?(ins[v]?dfn[v]:tim):(tarjan(v),low[v]));
  if(dfn[u]==low[u]){++n; do{col[stk[top]]=n,ins[stk[top]]=0;} while(stk[top--]!=u);}
}
int main(){
  scanf("%d\n",&m);
  for(int x,y,z,i=1;i<m;i++){
    for(int i=0;i<3;i++)get();y=get(),mrk[y]=1;
    for(int i=0;i<7;i++)get();x=get(),z=get();
    if(x+'a'-1!='1')G[x].push_back(y);
    if(z+'a'-1!='n')G[y].push_back(z);
  }
  for(int i=1;i<=26;i++)if(!dfn[i]&&mrk[i])tarjan(i);
  for(int i=1;i<=26;i++)for(int j:G[i])if(col[i]!=col[j])E[col[i]].push_back(col[j]);
  dp[(1<<n)-1]=1;
  for(int x=(1<<n)-1;x;x--){
    for(int i=1;i<=n;i++)deg[i]=0;
    for(int i=1;i<=n;i++)if((x>>i-1)&1)for(int j:E[i])deg[j]++;
    for(int i=1;i<=n;i++)if(((x>>i-1)&1)&&!deg[i])dp[x^(1<<i-1)]+=dp[x];
  }
  for(int i=1;i<=n;i++)fac*=i;
  printf("%d %lld/%lld\n",n,dp[0]/std::__gcd(dp[0],fac),fac/std::__gcd(dp[0],fac));
}//dfasdfsdafadsf