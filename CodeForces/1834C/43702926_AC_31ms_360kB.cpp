#include<bits/stdc++.h>
using namespace std;
int T,n;
string x,y;
int calc(){
  int ret=0;
  for(int i=0;i<n;i++)
    if(x[i]!=y[i]){
      ret++;
    }
  if(!ret)++ret;
  return ret;
}
int solve(){
  if(x==y){
    return 0;
  }
  int ans=INT_MAX;
  int t=calc();
  if(t&1){
    ans=min(ans,t*2-1);
  }else{
    ans=min(ans,t*2);
  }
  reverse(x.begin(),x.end());
  t=calc();
  if(t&1){
    ans=min(ans,t*2);
  }else{
    ans=min(ans,t*2-1);
  }
  return ans;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>x>>y;
    cout<<solve()<<endl;
  }
}