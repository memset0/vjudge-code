#include<bits/stdc++.h>
#ifndef memset0
  #define endl '\n'
#endif
using namespace std;
using ll=long long;
using vi=vector<int>;
const int N=2e3+9,mod=1e9+7,inv6=(mod+1)/6;
int T,n,s[N],ans;
long long a,b;
vi norm(const vector<long long> &b){
  vi a(b.size());
  for(size_t i=0;i<b.size();i++){
    a[i]=b[i]%mod;
    if(a[i]<0)a[i]+=mod;
  }
  return a;
}
vi operator*(const vi &a,const vi &b){
  vi c(a.size()+b.size()-1);
  for(size_t i=0;i<a.size();i++)
    for(size_t j=0;j<b.size();j++){
      c[i+j]=(c[i+j]+(ll)a[i]*b[j])%mod;
    }
  return c;
}
long long divn(long long x){
  if(x>=0)return x/n;
  return -((-x+n-1)/n);
}
long long getl(long long x){return divn(a-x+n-1);}
long long getr(long long x){return divn(b-x);}
void push(long long n,vi x){
  if(n<0)return;
  int m=n%mod;
  int m2=(ll)m*(m+1)/2%mod;
  if(x.size()>0)ans=(ans+(ll)(m+1)*x[0])%mod;
  if(x.size()>1)ans=(ans+(ll)m2*x[1])%mod;
  if(x.size()>2)ans=(ans+(ll)m*(m+1)%mod*(m*2+1)%mod*inv6%mod*x[2])%mod;
  if(x.size()>3)ans=(ans+(ll)m2*m2%mod*x[3])%mod;
}
void push(long long l,long long r,vi x){
  // cerr<<"push "<<l<<" "<<r<<" ";for(int v:x)cerr<<v<<",";cerr<<endl;
  if(l<0)l=0;
  if(l<=r){
    push(r,x);
    for(int i=0;i<x.size();i++){
      if(x[i])x[i]=mod-x[i];
    }
    push(l-1,x);
  }
  // cerr<<"ans="<<ans<<endl;
}
int main(){
#ifdef memset0
  freopen("F.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>a>>b;
    for(int i=0;i<n;i++)cin>>s[i];
    ans=0;
    for(int i=0;i<n;i++){
      push(
        getl(i),
        getr(i),
        norm({s[i],n})*norm({i-a+1,n})*norm({b+1-i,-n})
      );
    }
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        if(s[i]>s[j]&&(s[i]-s[j])%n==0){
          int d=(s[i]-s[j])/n;
          push(
            getl(i),
            getr(j)-d,
            vi{2}*norm({s[i],n})*norm({i-a+1,n})*norm({b+1-j-d*n,-n})
          );
        }
    for(int i=0;i<n;i++)
      for(int j=i+1;j<n;j++)
        if(s[i]==s[j]){
          push(
            getl(i),
            getr(j),
            vi{2}*norm({s[i],n})*norm({i-a+1,n})*norm({b+1-j,-n})
          );
        }
    cout<<ans<<endl;
  }
}