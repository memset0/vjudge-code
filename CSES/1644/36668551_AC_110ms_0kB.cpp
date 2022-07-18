#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,x,y,a[N];
long long ans=LLONG_MIN,s[N];
multiset<long long> p;
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n>>x>>y;
  for(int i=1;i<=n;i++)cin>>a[i],s[i]=s[i-1]+a[i];
//  for(int i=1;i<=n;i++)cerr<<s[i]<<" \n"[i==n];
  for(int i=1;i<=n;i++){
    if(i-x>=0)p.insert(s[i-x]);
    if(i-y-1>=0)p.erase(p.find(s[i-y-1]));
    if(p.size()){
      ans=max(ans,s[i]-*p.begin());
//      cerr<<i<<" "<<s[i]<<" "<<*p.begin()<<" "<<p.size()<<endl;
    }
  }
  cout<<ans<<endl;
}