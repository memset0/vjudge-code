#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 998244353
#define Maxn 105
const int M=1e5+7,p=998244353;
struct edge{
    int u,t,w;
}e[M];
using namespace std;
ll powM(ll a,int t=mod-2)
{
  ll ans=1;
  while(t){
    if (t&1)ans=ans*a%mod;
    a=a*a%mod;t>>=1;
  }return ans;
}
int n,m;
ll *a[Maxn],_a[Maxn][Maxn];
ll det(ll **a)
{
  ll ans=1;bool tr=0;
  for (int j=1;j<n;j++){
    for (int i=j;i<n;i++)
      if (a[i][j]){
        if (i!=j){
          swap(a[i],a[j]);
          tr=!tr;
        }break;
      }
      if (a[j][j]==0)return 0;
      ans=ans*a[j][j]%mod;
      ll t=powM(a[j][j]);
      for (int k=j;k<n;k++)a[j][k]=t*a[j][k]%mod;
    for (int i=j+1;i<n;i++){
        t=mod-a[i][j];
        for (int k=j;k<n;k++)
          a[i][k]=(a[i][k]+t*a[j][k])%mod;
    }
  }return tr? (mod-ans)%mod : ans;
}
int op;
int main()
{
    int t; cin>>t;
    while(t--){
        memset(_a,0,sizeof(_a));
        scanf("%d%d",&n,&m);
        for (int i=1;i<=n;i++)a[i]=_a[i];
        for(int i=1;i<=m;i++){
            scanf("%d%d%d",&e[i].u,&e[i].t,&e[i].w);
            
            a[e[i].u][e[i].u]++,a[e[i].t][e[i].t]++;
            a[e[i].u][e[i].t]=(a[e[i].u][e[i].t]-1+p)%p;
            a[e[i].t][e[i].u]=(a[e[i].t][e[i].u]-1+p)%p;
        }
        long long v=det(a),w=0;
        for(int z=0;z<=30;z++){
            memset(_a,0,sizeof(_a));
            for (int i=1;i<=n;i++)a[i]=_a[i];
            for(int i=1;i<=m;i++){
            if((e[i].w&(1<<z))==0) continue;
//            cout<<i<<"wwwww"<<" "<<(e[i].w&(1<<z))<<" "<<(1<<z)<<endl;
            a[e[i].u][e[i].u]++,a[e[i].t][e[i].t]++;
            a[e[i].u][e[i].t]=(a[e[i].u][e[i].t]-1+p)%p;
            a[e[i].t][e[i].u]=(a[e[i].t][e[i].u]-1+p)%p;
            }
            int s=det(a);
            w=(w+1ll*s*(1ll<<z))%p;
        }
        cout<<w*powM(v)%p<<endl;
    }
      
//  printf("%lld",det(a));
  return 0;
}