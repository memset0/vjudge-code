#include<bits/stdc++.h>
#define double __float128 
using namespace std;
const int N=1e6+10;
const double K=1e6;
int n,a[N];
double f[N],s,sf,sg;
int main(){
#ifdef memset0 
  freopen("1.in","r",stdin);
#endif
  cin.tie(0),ios::sync_with_stdio(0);
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i],f[i]=a[i]/K;
  for(int i=1;i<=n;i++){
    double t=n-f[i];
    sf+=1/t;
    sg+=(1-f[i])/t;
  }
//  cout<<sf<<" "<<sg<<endl;
  s=(sf/(1-sg))*((double)(n-1)/n);
#undef double
  printf("%.9lf\n",(double)s);
}