#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int T,n,a[N],f[N],g[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif 
	ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n;
    for(int i=1;i<=n;i++){
      cin>>a[i];
    }
    fill(f+1,f+n+1,0);
    fill(g+1,g+n+1,-19260817);
    for(int i=1;i<=n;i++){
      f[i]=max(f[i-1],i+g[a[i]]);
      if(i){
        g[a[i]]=max(g[a[i]],f[i-1]-i+1);
      }
    }
//    for(int i=1;i<=n;i++)cerr<<f[i]<<" \n"[i==n];
//    for(int i=1;i<=n;i++)cerr<<g[i]<<" \n"[i==n];
    cout<<f[n]<<endl;
  }
}