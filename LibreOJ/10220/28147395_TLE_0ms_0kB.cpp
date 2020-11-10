#include <bits/stdc++.h>
using namespace std;
#define f1(a,b,c) for (int c = a; c <= b; c++)
#define f2(a,b,c) for (int c = a; c >= b; c--)
#define f3(a,b,c) for (int c = a; c; c = b)
#define so1(a,n) sort(a + 1, a + n + 1, mycmp);
#define so2(a,n) sort(a + 1, a + n + 1);
#define re(a,n) reverse(a + 1, a + n + 1);
#define ll long long
#define itn int
#define ubt int
#define mp make_pair
#define pb push_back
#define pii pair<int, int>
#define pll pair<ll, ll>
const int twx=3;
const int inf=0x3f3f3f3f;
ll read(){
  ll sum=0;
  ll flag=1;
  char c=getchar();
  while(c<'0'||c>'9'){
    if(c=='-'){
      flag=-1;
    }
    c=getchar();
  }
  while(c>='0'&&c<='9'){
    sum=((sum*10)+c-'0');
    c=getchar();
  }
  return sum*flag;
}
struct LV{
  ll num[twx][twx];
}ans,base;
int n,m;
int MOD;
void make(){
  base.num[1][1]=base.num[1][2]=base.num[2][1]=1;
  ans.num[1][1]=ans.num[1][2]=1;
}
LV mul(LV a,LV b){
  LV c;
  memset(c.num,0,sizeof c.num);
  f1(1,2,i){
    f1(1,2,j){
      f1(1,2,k){c.num[i][j]=(c.num[i][j]+a.num[i][k]*b.num[k][j])%MOD;}
    }
  }
  return c;
}
LV POW(int n){
  while(n){
    if(n&1){
      ans=mul(ans,base);
    }
    base=mul(base,base);
    n>>=1;
  }
}
void init(){
  n=read();
  MOD=read();
}
void print(){
  if(n<=2){
    puts("1");
  }else{
    POW(n-2);
    printf("%lld\n",ans.num[1][1]);
  }
}
int main(){
  init();
  make();
  print();
  return 0;
}
