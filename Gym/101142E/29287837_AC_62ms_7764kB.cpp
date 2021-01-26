#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N=1e5+9,mod=1004535809,A=998244353,B=1e9+9;
inline int qp(int a,int b){
  int ret=1;
  if(b<0)a=qp(a,mod-2),b=-b;
  for(;b;b>>=1,a=1ll*a*a%mod)
    if(b&1)ret=1ll*ret*a%mod;
  return ret;
}
inline void add(int &x,int y){
  if((x+=y)>=mod)x-=mod;
}
int l,n,m,lc[N],md,num,lx,ly,px[N],py[N];
char c[N];
typedef map<pair<int,int>,int> mp;
mp u;
int main(){
  freopen("easy.in","r",stdin);
  freopen("easy.out","w",stdout);
  scanf("%d",&l);
  l=0;
  while(getchar()!='\n');
  char ch;
  for(int i=1;(ch=getchar())!='\n';++i)
    if(ch=='l'||ch=='r'||ch=='u'||ch=='d'){
      c[++l]=ch,lc[l]=i;
    }
  scanf("%d%d",&n,&m);
  while(getchar()!='\n');
  for(int i=1;i<=n;++i)
    for(int j=1;(ch=getchar())!='\n';++j)
      if(ch=='X'){
        ++num,add(md,ll(qp(A,i))*qp(B,j)%mod);
        if(!lx) lx=i,ly=j;
      }
  for(int i=1,x=0,y=0;i<=l;++i){
    if(c[i]=='l')--y;
    if(c[i]=='r')++y;
    if(c[i]=='u')--x;
    if(c[i]=='d')++x;
    px[i]=x,py[i]=y;
  }
  u[make_pair(0,0)]=1;
  for(int i=1,s=0,t=1,cnt=1,hash=1;i<=l;++i){
    for(;s<i-1;++s){
      mp::iterator it=u.find(make_pair(px[s],py[s]));
      if(it->second==1){
        u.erase(it);
        --cnt,add(hash,mod-ll(qp(A,px[s]))*qp(B,py[s])%mod);
      }else --it->second;
    }
    for(;t<=l&&cnt<num;++t){
      mp::iterator it=u.find(make_pair(px[t],py[t]));
      if(it==u.end()){
        u[make_pair(px[t],py[t])]=1;
        ++cnt,add(hash,ll(qp(A,px[t]))*qp(B,py[t])%mod);
      }else ++it->second;
    }
    if(cnt<num){
      puts("NO");
      return 0;
    }
    mp::iterator it=u.begin();
    if(ll(hash)*qp(A,lx-it->first.first)%mod*qp(B,ly-it->first.second)%mod==md){
      printf("YES\n%d %d\n",lc[i],lc[t-1]);
      return 0;
    }
  }
}//dasfasdfsaf