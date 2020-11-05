#include<bits/stdc++.h>
using namespace std;
const int N=22;
int n;
double ans,a[N],b[N],c[N],d[N];
long long fac[N];
pair<double,long long> u,v;
priority_queue<pair<double,long long>> q;
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  scanf("%d%lf%lf%lf%lf",&n,&a[1],&b[1],&c[1],&d[1]);
  a[0]=b[0]=c[0]=d[0]=fac[0]=fac[1]=1;
  for(int i=2;i<=n;i++)a[i]=a[i-1]*a[1],b[i]=b[i-1]*b[1],c[i]=c[i-1]*c[1],d[i]=d[i-1]*d[1],fac[i]=fac[i-1]*i;
  for(int aa=0;aa<=n;aa++)  
    for(int bb=0;aa+bb<=n;bb++)
      for(int cc=0;aa+bb+cc<=n;cc++){
        int dd=n-aa-bb-cc;
        q.push({-a[aa]*b[bb]*c[cc]*d[dd],fac[n]/fac[aa]/fac[bb]/fac[cc]/fac[dd]});
      }
  while(q.size()){
    u=q.top(),q.pop();
    if(u.second>=2){
      ans-=(u.second>>1)*u.first*2;
      q.push({u.first*2,u.second>>1});
      if(u.second&1)q.push({u.first,1});
    }else if(q.size()){
      v=q.top(),q.pop();
      ans-=u.first+v.first;
      q.push({u.first+v.first,1});
      if(v.second>1)q.push({v.first,v.second-1});
    }
  }
  printf("%.12lf\n",ans);
}