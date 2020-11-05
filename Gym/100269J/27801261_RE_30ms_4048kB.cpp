
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10,mod=1e9;
int n,a[N];
string s;
namespace seg{
  int sum[N];
  pair<int,int> val[N<<2];
  inline pair<int,int> merge(const pair<int,int> &a,const pair<int,int> &b){
    return a.first<=b.first?a:b;
  }
  void build(int u,int l,int r){
    if(l==r)return val[u]={sum[l],l},void(0);
    int mid=(l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
    val[u]=merge(val[u<<1],val[u<<1|1]);
  }
  pair<int,int> query(int u,int ql,int qr,int l,int r){
    if(ql==l&&qr==r)return val[u];
    int mid=(l+r)>>1;
    if(qr<=mid)return query(u<<1,ql,qr,l,mid);
    if(ql>mid)return query(u<<1|1,ql,qr,mid+1,r);
    return merge(query(u<<1,ql,mid,l,mid),query(u<<1|1,mid+1,qr,mid+1,r));
  }
  void init(){
    for(int i=0;i<s.length();i++){
      sum[i]=i?sum[i-1]:0;
      if(s[i]=='(')sum[i]++;
      if(s[i]==')')sum[i]--;
    }
    build(1,0,(int)s.length()-1);
  }
  inline int ask(int l,int r){return query(1,l,r,0,s.length()-1).second;}
}
struct z{
  int x;
  inline z(){x=0;}
  inline z(int t){x=t;}
  inline void operator-=(z a){(x-=a.x)<0&&(x+=mod);}
  inline void operator+=(z a){(x+=a.x)>=mod&&(x-=mod);}
  inline void operator*=(z a){x=(long long)x*a.x%mod;}
  friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
  friend inline z operator-(z a,z b){return ((a.x-=b.x)<0&&(a.x+=mod)),a;}
  friend inline z operator+(z a,z b){return ((a.x+=b.x)>=mod&&(a.x-=mod)),a;}
}p[11];
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
struct maton{
  int op;
  maton *l,*r;
  vector<z> v;
  void calc(int t=0){
    if(1<=op&&op<=3)r->calc(t+1),l->calc(t+1);
    if(4<=op&&op<=6)r->calc(t+1);
    if(op==1){
      v.resize(max(l->v.size(),r->v.size()));
      for(int i=0;i<l->v.size();i++)v[i]+=l->v[i];
      for(int i=0;i<r->v.size();i++)v[i]+=r->v[i];
    }else if(op==2){
      v.resize(max(l->v.size(),r->v.size()));
      for(int i=0;i<l->v.size();i++)v[i]+=l->v[i];
      for(int i=0;i<r->v.size();i++)v[i]-=r->v[i];
    }else if(op==3){
      v.resize(l->v.size()+r->v.size()-1);
      for(int i=0;i<l->v.size();i++)
        for(int j=0;j<r->v.size();j++)  
          v[i+j]+=l->v[i]*r->v[j];
    }else if(op==4){
      v=l->v;
      for(z &x:v)x=0-x;
    }else if(op==5){
      v.resize((r->v.size()<<1)-1);
      for(int i=0;i<r->v.size();i++)
        for(int j=0;j<r->v.size();j++)  
          v[i+j]+=r->v[i]*r->v[j];
    }else if(op==6){
      v.resize(1);
      for(int i=0;i<r->v.size();i++)v[0]+=p[i]*r->v[i];
    }
    // for(int x=t;x--;)cerr<<"  ";cerr<<"{"<<op<<"} ["<<v.size()<<"] ";for(z x:v)cerr<<x.x<<" ";cerr<<endl;
  }
};
maton* build(int l,int r){
  // cerr<<"build:"<<l<<","<<r<<" ";for(int i=l;i<=r;i++)cerr<<s[i];cerr<<endl;
  maton *u=new maton();
  if(s[l]=='-'||s[l]=='+'||s[l]=='*'){
    u->op=s[l]=='-'?4:(s[l]=='*'?5:6);
    u->r=build(l+(s[l]=='-'?1:2),r);
  }else if(s[l]=='('){
    int i=seg::ask(l,r);
    if(i==r)u=build(l+1,r-1);
    else{
      ++i;
      u->op=s[i]=='+'?1:(s[i]=='-'?2:3);
      u->l=build(l,i-1);
      u->r=build(i+1,r);
    }
  }else{
    int i=l;
    while(i<=r&&s[i]!='+'&&s[i]!='-'&&s[i]!='*')i++;
    if(i>r){
      if(s[l]=='X'){
        u->v={0,1};
      }else if(s[l]=='N'){
        u->v={n};
      }else{
        u->v={0};
        while(l<=r)u->v[0]=u->v[0]*10+(s[l]-'0'),l++;
      }
    }else{
      u->op=s[i]=='+'?1:(s[i]=='-'?2:3);
      u->l=build(l,i-1);
      u->r=build(i+1,r);
    }
  }
  return u;
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#else
  freopen("j.in","r",stdin),freopen("j.out","w",stdout);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n,p[0]=n;
  for(int i=1;i<=n;i++)cin>>a[i];
  for(int i=1;i<=10;i++)for(int j=1;j<=n;j++)p[i]+=fpow(a[j],i);
  cin>>s;
  seg::init();
  maton *rt=build(0,s.length()-1);
  rt->calc();
  cout<<rt->v[0].x<<endl;
}
