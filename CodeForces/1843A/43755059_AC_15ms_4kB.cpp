#include<bits/stdc++.h>
using namespace std;
const int N=109;
int T,n,a[N];
void solve(){
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i];
  sort(a+1,a+n+1);
  long long ans=0;
  for(int i=1;i<=(n>>1);i++){
    ans+=a[n-i+1]-a[i];
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