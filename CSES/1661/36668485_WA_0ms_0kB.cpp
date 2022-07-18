#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,k,a[N],s[N];
long long ans;
map<long long,int> p;
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n>>k;
  for(int i=1;i<=n;i++)cin>>a[i],s[i]=s[i-1]+a[i];
  for(int i=0;i<=n;i++){
    ans+=p[s[i]-k];
    p[s[i]]+=1;
  }
  cout<<ans<<endl;
}