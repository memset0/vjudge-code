//GGGGGGGGGGGGGGGGGGG
#include<bits/stdc++.h>
using namespace std;
using ll=__int128;
const int N=20;
int T,m,n,l,a[N],tmp[N];
ll p[N];
string s;
ll gcd(ll x,ll y){
  return y?gcd(y,x%y):x;
}
void write(ll x){
  if(x==0){
    putchar('0');
    return;
  }
  static int stk[100],top;
  top=0;
  while(x){
    stk[++top]=x%10+'0';
    x/=10;
  }
  while(top){
    putchar(stk[top--]);
  }
}
int main(){
#ifdef memset0
  freopen("G.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>m>>s;
    n=0,l=s.length();
    for(int i=l-1;i>=0;i--)
      if(s[i]==s[0]){
        s[i]=1;
      }
    for(int i=0;i<l;i++){
      tmp[i]=s[i];
    }
    sort(tmp,tmp+l);
    n=unique(tmp,tmp+l)-tmp;
    for(int i=0;i<l;i++){
      a[i]=lower_bound(tmp,tmp+n,s[i])-tmp;
    }
    // for(int i=0;i<l;i++)cerr<<a[i]<<" \n"[i+1==l];
    memset(p,0,n<<4);
    ll x=1;
    for(int i=l-1;i>=0;i--){
      p[a[i]]+=x;
      x*=m;
    }
    ll g=0;
    for(int i=0;i<n;i++){
      g=gcd(g,p[i]);
    }
    ll ans=g;
    // fprintf(stderr,"n=%d m=%d\n",n,m);
    // write(g),putchar('\n');
    // for(int i=0;i<n;i++)write(p[i]),putchar(" \n"[i+1==n]);
    if(m==n){
      ll sum=0;
      for(int i=0;i<n;i++){
        p[i]/=g;
      }
      for(int i=0;i<n;i++){
        sum+=p[i]*(n-i-1);
      }
      if(n>2){
        for(int i=1;i<n;i++){
          sum=gcd(sum,p[i]-p[i-1]);
        }
      }
      if(sum<0)sum=-sum;
      ans*=sum;
    }
    write(ans);
    putchar('\n');
  }
}