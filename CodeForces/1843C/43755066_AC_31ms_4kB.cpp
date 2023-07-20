#include<bits/stdc++.h>
using namespace std;
int T;
void solve(){
  long long n;
  cin>>n;
  long long ans=0;
  while(n){
    ans+=n;
    n>>=1;
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