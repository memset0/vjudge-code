#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,k,ans,a[N];
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n>>k;
  for(int i=1;i<=n;i++)cin>>a[i];
  int l=1,r=1,s=a[1];
  while(r<=n){
    while(s>=k){
      if(s==k)ans++;
      s-=a[l++];
    }
    s+=a[++r];
  }
  cout<<ans<<endl;
}