#include<bits/stdc++.h>
using namespace std;
const int N=505,M=105,mod=2520;
int n,m,x[N],r[N],g[N],c[N],L[N],R[N],cnt[M];
double ans[N],res[N];
bitset<M> mrk[N];
inline int gcd(int n,int m){return m?gcd(m,n%m):n;}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>x[i]>>r[i]>>g[i];
    c[i]=(r[i]+g[i])/gcd(r[i]+g[i],mod);
    if(c[i]%2==0)c[i]=8;
    if(c[i]%3==0)c[i]=9;
    L[i]=-x[i]%(r[i]+g[i]),L[i]<0&&(L[i]+=r[i]+g[i]);
    R[i]=(-x[i]+r[i])%(r[i]+g[i]),R[i]<0&&(R[i]+=r[i]+g[i]);
  }
  for(int u=0;u<mod;u++){
    memset(res,0,sizeof(res));
    memset(cnt,0,sizeof(cnt));
    memset(mrk,0,sizeof(mrk));
    res[0]=1;
    for(int i=1;i<=n;i++){
      res[i]=res[i-1]/(c[i]-cnt[c[i]]);
      for(int j=0;j<c[i];j++){
        int k=(u+j*mod)%(r[i]+g[i]);
        if(!mrk[c[i]][j]&&(L[i]<R[i]&&L[i]<=k&&k<R[i]||L[i]>R[i]&&(L[i]<=k||k<R[i])||L[i]==R[i]&&!g[i])){
          mrk[c[i]][j]=1,++cnt[c[i]];
        }
      }
      // printf("> %d %d %d [%d %d] %.12lf\n",i,c[i],cnt[c[i]],L[i],R[i],res[i]);
      if((res[i]*=c[i]-cnt[c[i]])==0)break;
    }
    for(int i=0;i<=n;i++)ans[i]+=res[i]-res[i+1];
    // for(int i=0;i<=n;i++)printf("%.12lf%c",res[i]," \n"[i==n]);
  }
  for(int i=0;i<=n;i++)printf("%.12lf\n",ans[i]/mod);
}