#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,a[N],b[N],c[N],d[N],vis[N],ans[N],pos[N];
queue<int> q;
vector<int> e[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#else
  freopen("insider.in","r",stdin);
  freopen("insider.out","w",stdout);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m;
  for(int i=1;i<=m;i++){
    cin>>a[i]>>b[i]>>c[i];
    e[a[i]].push_back(i);
    e[b[i]].push_back(i);
    e[c[i]].push_back(i);
    d[b[i]]++;
  }
  for(int i=1;i<=n;i++)if(!d[i])q.push(i);
  int L=1,R=n,u,cntl,cntr;
  while(q.size()){
    u=q.front(),q.pop(),vis[u]=1,cntl=cntr=0;
    for(int v:e[u])if(u==b[v]){
      if(vis[a[v]]^vis[c[v]]){
        pos[a[v]]<L?cntr++:cntl++;
      }
    }else{
      if(vis[a[v]]&&vis[c[v]]){
        pos[a[v]^c[v]^u]<L?cntl++:cntr++;
      }else{
        if(!--d[b[v]])q.push(b[v]);
      }
    }
    if(cntl<=cntr){
      pos[u]=L,ans[L]=u,L++;
    }else{
      pos[u]=R,ans[R]=u,R--;
    }
  }
  for(int i=1;i<=n;i++)cout<<ans[i]<<" \n"[i==n];
}