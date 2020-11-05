#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int a[N];
struct BIT{
  int c[N];
  inline void add(int x,int s){for(;x<N;x+=x&-x)c[x]=max(c[x],s);}
  inline int sum(int x){int s=0;for(;x;x-=x&-x)s=max(s,c[x]);return s;}
}tr1,tr2;
int n,ans,dp1[N],dp2[N];
int main(){
  freopen("improvements.in","r",stdin);
  freopen("improvements.out","w",stdout);
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  int x;
  for(int i=1;i<=n;++i)cin>>x,a[x]=i;
  for(int i=1;i<=n;++i){
    dp1[i]=tr1.sum(a[i])+1;
    tr1.add(a[i],dp1[i]);
		dp1[i]=max(dp1[i],dp1[i-1]);
  }
  for(int i=n;i>=1;--i){
    dp2[i]=tr2.sum(a[i])+1;
    tr2.add(a[i],dp2[i]);
		dp2[i]=max(dp2[i],dp2[i+1]);
  }
  for(int i=1;i<=n;++i)ans=max(ans,dp1[i]+dp2[i+1]);
  cout<<ans<<endl;
}