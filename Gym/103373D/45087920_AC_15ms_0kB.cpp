#include<bits/stdc++.h>
using namespace std;
const int N=309;
int n;
double f[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  cin>>n;
  for(int i=2;i<=n;i++){
    f[i]+=1./(n-1);
  }
  for(int i=2;i<=n;i++){
    double g=f[i]/(n-i+1);
    for(int j=i+1;j<=n;j++){
      f[j]+=g;
    }
  }
  cout<<fixed<<setprecision(12)<<f[n]<<endl;
}///