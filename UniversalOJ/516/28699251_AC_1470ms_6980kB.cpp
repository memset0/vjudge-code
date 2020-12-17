#include<bits/stdc++.h>
const int N=2e3+10,mod=998244353;
int n,ans;
char s[N];
struct matrix{
  int a[27][27];
  friend inline matrix operator*(const matrix &a,const matrix &b){
    matrix c; memset(c.a,0,sizeof(c.a));
    for(int i=0;i<27;i++)
      for(int j=0;j<27;j++)
        for(int k=0;k<27;k++)
          c.a[i][j]=(c.a[i][j]+(int64_t)a.a[i][k]*b.a[k][j])%mod;
    return c;
  }
}A[27],F[N],S,I;
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  scanf("%d%s",&n,s+1);
  for(int i=0;i<27;i++)I.a[i][i]=1;
  for(int c=0;c<27;c++){
    A[c]=I;
    for(int i=0;i<27;i++)A[c].a[c][i]=1;
    A[c].a[c][c]=1;
  }
  F[n+1]=I;
  for(int i=n;i>=1;i--){
    F[i]=F[i+1]*A[s[i]-'a']*F[i+1];
  }
  S.a[26][0]=1;
  S=F[1]*S;
  for(int i=0;i<27;i++)ans=(ans+S.a[i][0])%mod;
  printf("%d\n",(ans+mod-1)%mod);
}