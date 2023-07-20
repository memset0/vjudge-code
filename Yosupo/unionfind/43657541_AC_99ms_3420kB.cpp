#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,q,t,u,v,fa[N];
inline int find(int x){
  if(fa[x]==x)return x;
  return fa[x]=find(fa[x]);
}
int main(){
  cin.tie(0),ios::sync_with_stdio(0);
  cin>>n>>q;
  for(int i=1;i<=n;i++)fa[i]=i;
  while(q--){
    cin>>t>>u>>v;
    if(t==0){
      fa[find(u)]=find(v);
    }else{
      if(find(u)==find(v)){
        cout<<1<<endl;
      }else{
        cout<<0<<endl;
      }
    }
  }
  return 0;
} 