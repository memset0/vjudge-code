#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,m,k,deg[N];
set<int> s;
vector<int> seq,G[N];
vector<pair<int,int>> ans;
void add(int u,int v){ans.push_back({u,v}),G[u].push_back(v),++deg[v];}
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
    if(s.size()==1||!k){
      seq.push_back(*s.begin()),s.erase(s.begin());
    }else{
      vector<int> t;
      for(int x:s)if(t.size()<=k)t.push_back(x);else break;
      s.erase(t[k]),seq.push_back(t[k]);
      int u=std::min(k,(int)s.size()-1);k-=u;
      for(int i=0;i<u-1;i++)add(t[i+1],t[i]);
      add(*--s.end(),t[u-1]);
      for(int i=0;i<u;i++)s.erase(t[i]);
    }
    for(int v:G[seq.back()])if(!--deg[v])s.insert(v);
  }
  for(int x:seq)cout<<x<<" ";cout<<endl;
  cout<<ans.size()<<endl;
  for(auto it:ans)cout<<it.first<<" "<<it.second<<endl;
}