#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
int T,n,res[N];
pair<int,int> ans[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>T;
  int n=1000000;
  for(int i=1;i<=n;i++)res[i]=(3*i-1)/7;
  ans[1]={res[1],1};
  for(int i=2;i<=n;i++){
    ans[i]=ans[i-1];
    if((long long)ans[i].first*i<(long long)ans[i].second*res[i]){
      ans[i]={res[i],i};
    }
  }
  while(T--){
    cin>>n;
    cout<<ans[n].first<<" "<<ans[n].second<<endl;
  }
}

#if 0
a/b < 3/7
7a < 3b
7a <= 3b - 1
max(a) = (3b - 1) / 7

ans[i].first/ans[i].second < res[i]/i
ans[i].first*i < ans[i].second*res[i]
#endif