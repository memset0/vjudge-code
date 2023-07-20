#include<bits/stdc++.h>
using namespace std;
const int N=5e5+9;
int n,m,a[N],b[N],l,r,q[N];
void push(int x,int i){
  while(l<=r&&x<=b[q[r]]){
    r--;
  }
  q[++r]=i;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n>>m;
  for(int i=1;i<=n;i++){
    cin>>a[i]; 
  }
  sort(a+1,a+n+1);
  for(int i=1;i<n;i++){
    b[i]=a[i+1]-a[i];
    if(b[i]==0){
      cout<<0<<endl;
      return 0;
    }
  }
  l=r=1,q[1]=1;
  for(int i=2;i<m;i++){
    push(b[i],i);
  }
  long long ans=1ll*(a[n]-a[1])*(a[n]-a[1]);
  for(int i=m;i<n;i++){
    while(q[l]<=i-m)l++;
    //assert(l<=r);
    ans=min(ans,1ll*b[q[l]]*(a[i]-a[i-m+1]));
    //cout<<i<<" "<<q[l]<<" "<<b[q[l]]<<" "<<a[i+1]<<" "<<a[i-m+1]<<endl;
    push(b[i],i);
  }
  cout<<ans<<endl;
}