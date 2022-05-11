#include<bits/stdc++.h>
const int mod=998244353,L=7;
typedef int matrix[L][L];
int n,m,ans;
inline void mul(matrix a,matrix b,matrix s){
  static matrix c;
  memset(c,0,sizeof(c));
  for(int i=0;i<L;i++)
    for(int j=0;j<L;j++)
      for(int k=0;k<L;k++)
        c[i][j]=(c[i][j]+(long long)a[i][k]*b[k][j])%mod;
  memcpy(s,c,sizeof(c));
}
int main(){
#ifdef local
  freopen("1.in","r",stdin);
#endif
  scanf("%d%d",&n,&m);
  if(m==1){
    ans=0;
  }else if(m==2){
    ans=((n&1)==0&&((n>>1)&1))?2:0;
  }else if(n&1){
    matrix a={
      {0,1},
      {m-1,m-2},
    };
    matrix s;
    memset(s,0,sizeof(s));
    s[0][0]=1;
    n--;
    while(n){
      if(n&1)mul(a,s,s);
      n>>=1,mul(a,a,a);
    }
    ans=(long long)m*s[1][0]%mod;
  }else{
    matrix a={
      {0,1,0,1,1,0,1},
      {1,0,1,0,0,1,1},
      {0,m-2,0,m-2,m-3,m-2,m-3},
      {m-2,0,m-2,0,m-2,m-3,m-3},
      {m-2,0,m-3,m-2,0,m-2,m-3},
      {0,m-2,m-2,m-3,m-2,0,m-3},
      {0,0,0,0,0,0,0},
    };
    for(int i=0;i<L-1;i++)
      for(int j=0;j<L;j++)
        a[L-1][j]=(a[L-1][j]-a[i][j])%mod;
    for(int i=0;i<L;i++)
      a[L-1][i]=((long long)(m-1)*(m-1)%mod-(m-2)+a[L-1][i]+mod+mod)%mod;
    matrix s;
    memset(s,0,sizeof(s));
    s[0][0]=1;
    n=(n>>1)-1;
    while(n){
      if(n&1)mul(a,s,s);
      n>>=1,mul(a,a,a);
    }
    ans=((long long)s[0][0]+s[2][0]+s[5][0]+s[6][0])%mod;
    ans=(long long)m*(m-1)%mod*ans%mod;
  }
  printf("%d\n",ans);
}