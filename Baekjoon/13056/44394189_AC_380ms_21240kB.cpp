#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
ll dp[123][20002];
const ll mod=1000000007;
int n,w,h;
int main(){
  scanf("%d%d%d",&n,&w,&h);
  dp[0][0]=1;
  for(int i=1;i<=w;i++){
    for(int r=0;r<=n;r++){
      for(int p=0;p<=h&&p<=r;p++){
        dp[i][r]=(dp[i][r]+dp[i-1][r-p])%mod;
      }
    }
  }
  ll ans=0;
  for(int i=0;i<=n;i++)ans=(ans+dp[w][i])%mod;
  for(int i=0;i<=h;i++){
    if(w*i<=n)ans=(ans-1+mod)%mod;
  }
  printf("%lld\n",ans);
}