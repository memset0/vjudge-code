// ==============================
//  author: memset0
//  website: https://memset0.cn
// ==============================
#include <bits/stdc++.h>
#define lowbit(x) ((x)&(-(x)))
const int maxn=5000;
int n,m,a,b,c,d,x,opt;
long long ans,s[4][maxn][maxn];
void modify(int a,int b,int x){
  for(int i=a;i<=n;i+=lowbit(i))
    for(int j=b;j<=m;j+=lowbit(j)){
      s[0][i][j]+=x;
      s[1][i][j]+=x*a;
      s[2][i][j]+=x*b;
      s[3][i][j]+=x*a*b;
    }
}
long long query(int a,int b){
  long long ans=0;
  for(int i=a;i;i-=lowbit(i))
    for(int j=b;j;j-=lowbit(j)){
      ans+=s[0][i][j]*a*b;
      ans-=s[1][i][j]*b;
      ans-=s[2][i][j]*a;
      ans+=s[3][i][j];
    }
  return ans;
}
void Modify(int a,int b,int c,int d,int x){
  modify(a,b,x);
  modify(a,d+1,-x);
  modify(c+1,b,-x);
  modify(c+1,d+1,x);
}
long long Query(int a,int b,int c,int d){
  long long ans=0;
  ans+=query(a,b);
  ans-=query(a,d+1);
  ans-=query(c+1,b);
  ans+=query(c+1,d+1);
  return ans;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  scanf("%d%d",&n,&m);
  while(~scanf("%d%d%d%d%d",&opt,&a,&b,&c,&d)){
    if(opt==1){
      scanf("%d",&x),Modify(a,b,c,d,x);
    }else{
      printf("%lld\n",Query(a,b,c,d));
    }
  }
  return 0;
}
