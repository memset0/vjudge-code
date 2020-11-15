#include<bits/stdc++.h>

struct TheCowDivOne{
  static const int N=1e3+10,mod=1e9+7;
  
  int pnt,phi[N],pri[N];
  bool vis[N];

  struct z {
    int x;
    z(int x=0):x(x){}
    friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
    friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
    friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
  }ans;
  inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}

  z C(int n,int m){
    // printf("C %d %d\n",n,m);
    m=std::min(m,n-m);
    z res=1;
    for(int i=1;i<=m;i++)res=res*i;
    res=fpow(res,mod-2);
    for(int i=n;i>=n-m+1;i--)res=res*i;
    return res;
  }

  void sieve(int n){
    phi[1]=1;
    for(int i=2;i<=n;i++){
      if(!vis[i])pri[++pnt]=i,phi[i]=i-1;
      for(int j=1;j<=pnt&&i*pri[j]<=n;j++){
        vis[i*pri[j]]=1;
        if(i%pri[j]==0){phi[i*pri[j]]=phi[i]*pri[j]; break;}
        else phi[i*pri[j]]=phi[i]*(pri[j]-1);
      }
    }
    // for(int i=1;i<=n;i++)printf("phi[%d] = %d\n",i,phi[i]);
  }

  int find(int n,int k){
		pnt=0;
		memset(vis,0,sizeof(vis));
		memset(phi,0,sizeof(phi));
		memset(pri,0,sizeof(pri));
    sieve(k);
    // printf("find %d %d\n",n,k);
    for(int i=1;i<=k;i++)if(k%i==0&&n%i==0){
      ans=ans+C(n/i,k/i)*phi[i]*(i & 1 ? 1 : k / i & 1 ? mod - 1 : 1);
      // printf("%d => %d %d %d\n",i,phi[i],k+k/i,C(n/i,k/i));
    }
    return (ans*fpow(n,mod-2)).x;
  }
};

#ifdef local
int main(){
  freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  int n,k;
  while(~scanf("%d%d",&n,&k)){
    printf("%d\n",(new TheCowDivOne())->find(n,k));
  }
}
#endif