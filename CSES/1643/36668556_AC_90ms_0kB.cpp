#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,a[N];
long long ans=LLONG_MIN,s[N];
multiset<long long> p;
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i],s[i]=s[i-1]+a[i];
  for(int i=0;i<=n;i++){
    if(p.size()){
      ans=max(ans,s[i]-*p.begin());
    }
    p.insert(s[i]);
  }
  cout<<ans<<endl;
}