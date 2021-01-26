#include<bits/stdc++.h>
using namespace std;
const int N=10010;
const long long inf=3e18;
int n;
long long m,a,b,x[N],y[N],f[N];
int main(){
#ifdef memset0
	freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m>>a>>b;
  for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
  f[1]=(long long)a*(m-y[1]);
  for(int i=2;i<=n;i++){
    long long L=x[i]-2ll*(m-y[i]);
    long long R=x[i];
    f[i]=inf;
    for(int j=i-1;j;j--){
      long long A=x[i]-x[j],B=m-y[j];
      long long delta=sqrt(8ll*A*B);
      L=max(L,x[i]-2ll*(A+B)-delta);
      if(x[i]-x[j]<=2ll*(m-y[j]))R=min(R,x[j]);
      else R=min(R,x[i]-2ll*(A+B)+delta);
      if(x[j]>=L&&x[j]<=R){
        f[i]=min(f[i],f[j]+(long long)a*(m-y[i])+(long long)b*A*A);
      }
    }
  }
  if(f[n]==inf)cout<<"impossible"<<endl;
  else cout<<f[n]<<endl;
}//dfadsfadf