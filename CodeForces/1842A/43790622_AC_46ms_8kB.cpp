#include<bits/stdc++.h>
using namespace std;
const int N=59;
int T,n,m,a[N],b[N]; 
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif 
	ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>m;
    long long sa=0,sb=0;
    for(int i=1;i<=n;i++)cin>>a[i],sa+=a[i];
    for(int i=1;i<=m;i++)cin>>b[i],sb+=b[i];
    if(sa==sb){
      cout<<"Draw"<<endl;
    }else if(sa>sb){
      cout<<"Tsondu"<<endl;
    }else{
      cout<<"Tenzing"<<endl;
    }
  }
}