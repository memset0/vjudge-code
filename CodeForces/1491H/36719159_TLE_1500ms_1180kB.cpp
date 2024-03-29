#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9,P=300,B=N/P+9;
int n,q,a[N],f[N],bln[N],bl[B],br[B],tag[B];
bool loc[B];
void build(int x){
  for(int i=bl[x];i<=br[x];i++)f[i]=a[i]<bl[x]?a[i]:f[a[i]];
  loc[x]=true;
  for(int i=bl[x];i<=br[x];i++)if(a[i]>=bl[x]){loc[x]=false;break;}
}
void update(int x,int l,int r,int v){
  if(l==bl[x]&&r==br[x]&&loc[x]){tag[x]+=v;return;}
  if(loc[x]){
    for(int i=bl[x];i<=br[x];i++)a[i]=max(1,a[i]-tag[x]);
    tag[x]=0;
  }
  for(int i=l;i<=r;i++)a[i]=max(1,a[i]-v);
  build(x); 
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n>>q,a[1]=f[1]=1,bln[1]=1;
  for(int i=2;i<=n;i++)cin>>a[i],bln[i]=i/P+2;
  for(int i=1;i<=n;i++)br[bln[i]]=i;
  for(int i=n;i>=1;i--)bl[bln[i]]=i;
  for(int i=2;i<=bln[n];i++)build(i);
  while(q--){
    int t,u,v,x,l,r;
    cin>>t;
//    cerr<<">>> "<<t<<endl;
    if(t==1){
      cin>>l>>r>>x;
      if(bln[l]==bln[r]){
        update(bln[l],l,r,x);
      }else{
        update(bln[l],l,br[bln[l]],x);
        update(bln[r],bl[bln[r]],r,x);
        for(int i=bln[l]+1;i<bln[r];i++)update(i,bl[i],br[i],x);
      }
    }else{
      cin>>u>>v;
      while(bln[u]!=bln[v]){
        if(u>v)swap(u,v);
//        cerr<<u<<" "<<v<<endl;
        v=f[v];
      } 
      while(u!=v){
        if(u>v)swap(u,v);
//        cerr<<u<<" "<<v<<"."<<endl;
        v=a[v]-tag[bln[v]];
      }
      cout<<v<<endl;
    }
  }
}
