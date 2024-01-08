#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9;
int n,a[N],dp[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>a[i];
    dp[i]=max(dp[i-1],dp[i-2]+a[i]);
  }
  cout<<dp[n]<<endl;
}