#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int T,n,m,q,a[N],op[N],s[N],l[N],r[N];
bool check(int t){
//  cerr<<"check"<<t<<endl;
  std::fill(a+1,a+n+1,0);
  for(int i=1;i<=t;i++)a[op[i]]=1;
  for(int i=1;i<=n;i++){
    s[i]=s[i-1]+a[i]; 
  }
  int ans=INT_MAX;
  for(int i=1;i<=m;i++){
//    cerr<<">>"<<l[i]<<" "<<r[i]<<" "<<s[r[i]]-s[l[i]-1]<<" "<<(r[i]-l[i]+1)-2*(s[r[i]]-s[l[i]-1])<<endl;
    ans=min(ans,(r[i]-l[i]+1)-2*(s[r[i]]-s[l[i]-1]));
  }
  return ans<0;
} 
void solve(){
  cin>>n>>m;
  for(int i=1;i<=m;i++)cin>>l[i]>>r[i];
  cin>>q;
  for(int i=1;i<=q;i++){
    cin>>op[i];
  }
  int l=1,r=q,mid,ans=-1;
  while(l<=r){
    mid=(l+r)>>1;
    if(check(mid)){
      ans=mid;
      r=mid-1;
    }else{
      l=mid+1;
    }
  }
  cout<<ans<<endl;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    solve();
  }
} 