#include<bits/stdc++.h>
using namespace std;
const int N=2e6+10;
int n,k,nxt[N],f[N][21];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>k;
  int x,y;
  for(int i=1;i<=n+n;++i) nxt[i]=i;
  for(int i=1;i<=k;++i){
    cin>>x>>y;
    if(y<x) y+=n;
    nxt[x]=max(nxt[x],y+1);
    x+=n,y+=n,y=min(y,n+n);
    nxt[x]=max(nxt[x],y+1);
  }
  for(int i=1;i<=n+n;++i)nxt[i]=max(nxt[i],nxt[i-1]);
  nxt[n+n+1]=n+n+1;
  for(int i=n+n+1;i>=1;--i){
    f[i][0]=nxt[i];
    for(int j=1;j<=20&&i+(1<<(j-1))<=n+n+1;++j) f[i][j]=f[f[i][j-1]][j-1];
  }
  int res=1e9;
  for(int i=1;i<=n;++i){
    int cur=i,ans=0;
    for(int j=20;j>=0;--j)
      if(f[cur][j]&&f[cur][j]<i+n)
        cur=f[cur][j],ans|=1<<j;
    if(nxt[cur]>=i+n)res=min(res,ans+1);
  }
  (res==1e9)?puts("impossible"):printf("%d\n",res);
}