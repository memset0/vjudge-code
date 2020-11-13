#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,k,deg[N];
set<int> s;
vector<int> seq,G[N];
vector<pair<int,int>> ans;
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#else
  freopen("graph.in","r",stdin);
  freopen("graph.out","w",stdout);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m>>k;
  for(int u,v,i=1;i<=m;i++)cin>>u>>v,++deg[v],G[u].push_back(v);
  for(int i=1;i<=n;i++)if(!deg[i])s.insert(i);
  while(s.size()){
    if(k>=s.size()-1){
      seq.push_back(*--s.end()),s.erase(--s.end()),k-=s.size();
      for(int x:s)ans.push_back({seq.back(),x});
    }else{
      seq.push_back(*s.begin()),s.erase(s.begin());
    }
  }
  for(int x:seq)cout<<x<<" ";cout<<endl;
  cout<<ans.size()<<endl;
  for(auto it:ans)cout<<it.first<<" "<<it.second<<endl;
}