#include<bits/stdc++.h>
using namespace std;
const int N=3e5+9;
int n,m,k,anc[N],siz[N];
long long ans;
map<int,int> G[N];
queue<pair<int,int> > que;
int find(int x){return anc[x]==x?x:anc[x]=find(anc[x]);}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m>>k;
  for(int u,v,w,i=0;i<m;i++){
    cin>>u>>v>>w;
    if(G[v][w]){
      que.push(make_pair(u,G[v][w]));
    }else{
      G[v][w]=u;
    }
  }
  for(int i=1;i<=n;i++)anc[i]=i;
  while(que.size()){
    int u=que.front().first,v=que.front().second;
//    fprintf(stderr,"%d %d\n",u,v);
    que.pop();
    u=find(u),v=find(v);
    if(u==v)continue;
    if(G[u].size()<G[v].size())swap(u,v);
    anc[v]=u;
    for(map<int,int>::iterator it=G[v].begin();it!=G[v].end();it++){
      if(G[u][it->first]){
        que.push(make_pair(it->second,G[u][it->first]));
      }else{
        G[u][it->first]=it->second;
      }
    }
    G[v].clear();
  }
//  for(int i=1;i<=n;i++)fprintf(stderr,"%d%c",find(i)," \n"[i==n]);
  for(int i=1;i<=n;i++)siz[find(i)]++;
  for(int i=1;i<=n;i++)ans+=(long long)siz[i]*(siz[i]-1)/2;
  cout<<ans<<endl;
}