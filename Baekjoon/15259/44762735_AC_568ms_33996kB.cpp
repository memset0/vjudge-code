#include<bits/stdc++.h>
using namespace std;
struct opt{
  int x,y,z;
  opt(int x=0,int y=0,int z=0):x(x),y(y),z(z){}
};
vector<opt> Op;
int n,m;
const int N=3e5+5;
int par[N],ans[N],sz[N],fa[N];
inline int find(int x){
  return par[x]==x?par[x]:par[x]=find(par[x]);
}
set<pair<int,int>> st;
typedef set<pair<int,int>>::iterator iter;
int main(){
  cin>>n;
  for(int i=1,x,y;i<=n;i++){
    scanf("%d%d",&x,&y);
    Op.push_back(opt(x,y,-i));
  }
  cin>>m;
  for(int x,y,i=1;i<=m;i++){
    scanf("%d%d",&x,&y);
    Op.push_back(opt(x,y,i));
    par[i]=i;
  }
  sort(Op.begin(),Op.end(),[&](opt a,opt b)->bool{return a.y==b.y?a.z>b.z:a.y>b.y;});
  for(auto p:Op){
    if(p.z<0){
      iter it=st.upper_bound(make_pair(p.x,0));
      if(it!=st.end()){
        sz[(*it).second]++;
      }
    }else{
      iter it=st.insert(make_pair(p.x,p.z)).first;
      if(next(it)!=st.end()){
        fa[p.z]=(*next(it)).second;
      }
      while(it!=st.begin()&&(*prev(it)).second>p.z){
        st.erase(prev(it));
      }
    }
  }
  for(int i=m;i;i--){
    ans[i]=sz[i];
    if(!fa[i])continue;
    int y=find(fa[i]);
    sz[y]+=sz[i];
    par[i]=y;
  }
  for(int i=1;i<=m;i++){
    printf("%d\n",ans[i]);
  }
}