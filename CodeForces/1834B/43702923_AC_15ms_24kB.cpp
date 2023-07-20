#include<bits/stdc++.h>
using namespace std;
int T,n;
string x,y;
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>x>>y;
    n=y.length();
    while(x.length()<n){
      x='0'+x;
    }
    int ans=0;
    for(int i=0;i<n;i++)
      if(x[i]!=y[i]){
        ans+=(y[i]-x[i]);
        ans+=(n-i-1)*9;
        break;
      }
    cout<<ans<<endl;
  }
} 