#include<bits/stdc++.h>
using namespace std;
const int N=59;
int n;
unsigned long long dp[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n;
  dp[0]=1;
  for(int i=0;i<=n;i++){
    dp[i+1]+=dp[i];
    dp[i+2]+=dp[i];
  }
  cout<<dp[n]<<endl;
}