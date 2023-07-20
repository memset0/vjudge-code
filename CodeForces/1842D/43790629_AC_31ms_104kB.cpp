#include<bits/stdc++.h>
using namespace std;
const int N=109;
int n,m;
long long inf,dis[N][N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  cin>>n>>m;
  memset(dis,63,sizeof(dis));
  inf=dis[0][0];
  for(int i=1;i<=n;i++){
    dis[i][i]=0;
  }
  for(int u,v,w,i=1;i<=m;i++){
    cin>>u>>v>>w;
    dis[u][v]=dis[v][u]=w;
  }
  for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++){
        dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
      }
  if(dis[1][n]==inf){
    cout<<"inf"<<endl;
    return 0;
  }
  vector<pair<long long,int>> ord;
  for(int i=1;i<=n;i++){
    ord.push_back(make_pair(dis[1][i],i));
  }
  sort(ord.begin(),ord.end());
  string cur(n,'0'),nxt;
  cur[0]='1',nxt=cur;
//  cerr<<cur<<endl;
  vector<pair<string,long long>> ans;
  for(int i=1,j;i<n;i=j){
    bool fl=false;
    j=i;
    while(j<n&&ord[i].first==ord[j].first){
      nxt[ord[j].second-1]='1';
      if(ord[j].second==n){
        fl=true;
      }
      j++;
    }
    ans.push_back(make_pair(cur,ord[i].first-ord[i-1].first));
    cur=nxt;
    if(fl){
      break;
    }
  }
  cout<<dis[1][n]<<" "<<ans.size()<<endl;
  for(int i=0;i<ans.size();i++){
    cout<<ans[i].first<<" "<<ans[i].second<<endl;
  }
}