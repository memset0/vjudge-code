#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int T,n,a[N];
void solve(){
  cin>>n;
  long long ans=0;
  for(int i=1;i<=n;i++){
    cin>>a[i];
    ans+=a[i]>0?a[i]:-a[i];
  }
  int cnt=0;
  for(int l=1,r;l<=n;l=r+1){
    r=l;
    if(a[l]<0){
      while(a[r]<=0&&r<=n)r++;
      --r;
      cnt++;
    }
  }
  cout<<ans<<" "<<cnt<<endl;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    solve();
  }
} 