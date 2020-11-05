#include<bits/stdc++.h>
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> inline void print(T x){
  if(x<0)putchar('-'),x=-x;
  if(x>9)print(x/10); putchar(x%10+'0');
}
template<class T> inline void print(T x,char c){print(x),putchar(c);}
const int N=2e5+10,mod=998244353;
int _,n,m,cnt,siz[N],vis[N],mid[N],ch[N][2],fa[N],l[N],r[N],dep[N],rev[N<<2];
struct z {
  int x;
  z(int x=0):x(x){}
  friend inline z operator*(z a,z b){return (long long)a.x*b.x%mod;}
  friend inline z operator-(z a,z b){return (a.x-=b.x)<0?a.x+mod:a.x;}
  friend inline z operator+(z a,z b){return (a.x+=b.x)>=mod?a.x-mod:a.x;}
}w[N<<2];
std::vector<z> ans;
inline z fpow(z a,int b){z s=1;for(;b;b>>=1,a=a*a)if(b&1)s=s*a;return s;}
inline void print(const std::vector<z> &a){for(int i=0;i<a.size();i++)printf("%d ",a[i].x); printf("\n");}
void dft(std::vector<z> &a,int lim){
  a.resize(lim);
  for(int i=0;i<lim;i++)if(i<rev[i])std::swap(a[i],a[rev[i]]);
  for(int len=1;len<lim;len<<=1)
    for(int i=0;i<lim;i+=(len<<1))
      for(int j=0;j<len;j++){
        z x=a[i+j],y=a[i+j+len]*w[j+len];
        a[i+j]=x+y,a[i+j+len]=x-y;
      }
}
std::vector<z> operator+(std::vector<z> a,const std::vector<z> &b){
  a.resize(std::max(a.size(),b.size()));
  for(int i=0;i<b.size();i++)a[i]=a[i]+b[i]; return a;
}
std::vector<z> operator-(std::vector<z> a,const std::vector<z> &b){
  a.resize(std::max(a.size(),b.size()));
  for(int i=0;i<b.size();i++)a[i]=a[i]-b[i]; return a;
}
std::vector<z> operator*(std::vector<z> a,std::vector<z> b){
  int len=a.size()+b.size()-1,lim=1,k=0;
  while(lim<len)lim<<=1,++k;
  for(int i=0;i<lim;i++)rev[i]=rev[i>>1]>>1|((i&1)<<(k-1));
  dft(a,lim),dft(b,lim);
  for(int i=0;i<lim;i++)a[i]=a[i]*b[i];
  dft(a,lim),std::reverse(&a[1],&a[lim]);
  z inv=fpow(lim,mod-2);
  for(int i=0;i<lim;i++)a[i]=a[i]*inv;
  return a.resize(len),a;
}
void shift(z x,std::vector<z> &dst,size_t dta){
  dst.resize(std::max(dst.size(),dta+1));
  dst[dta]=dst[dta]+x;
}
void shift(const std::vector<z> &src,std::vector<z> &dst,size_t dta){
  dst.resize(std::max(dst.size(),src.size()+dta));
  for(int i=0;i<src.size();i++)dst[i+dta]=dst[i+dta]+src[i];
}
void dfsInit(int &u,int l,int r,int dep){
  if(l==r){
    u=n-1+l;
  }else{
    u=++cnt;
    dfsInit(ch[u][0],l,mid[u],dep+1),fa[ch[u][0]]=u;
    dfsInit(ch[u][1],mid[u]+1,r,dep+1),fa[ch[u][1]]=u;
  }
  ::l[u]=l,::r[u]=r,::dep[u]=dep;
}
void printTree(int u,int fa=0){
  if(!u||vis[u])return;
  printf("\e[2mtree %d -> %d\e[0m\n",fa,u);
  printTree(ch[u][0],u);
  printTree(ch[u][1],u);
}
int calcSize(int u){
  if(!u||vis[u])return 0;
  return siz[u]=1+calcSize(ch[u][0])+calcSize(ch[u][1]);
}
std::pair<int,int> findSubTree(int u,int lim){
  if(!u||vis[u])return {-1,-1};
  if(siz[u]<lim)return {u,siz[u]};
  std::pair<int,int> x=ch[u][0]?findSubTree(ch[u][0],lim):std::make_pair(-1,-1);
  std::pair<int,int> y=ch[u][1]?findSubTree(ch[u][1],lim):std::make_pair(-1,-1);
  return x.second>y.second?x:y;
}
void calc(bool fl,int u,int mov,std::vector<z> &f){
  if(vis[u]||l[u]==r[u])return shift(1,f,mov+1);
  shift(1,f,mov+1);
  shift(mod-1,f,mov+3);
  calc(fl,ch[u][0],mov+(fl?2:1),f);
  calc(fl,ch[u][1],mov+(fl?1:2),f);
}
std::pair<std::vector<z>,std::vector<z>> fuck(int u){
  if(vis[u]||l[u]==r[u])return {{0,1},{0,1}};
  std::vector<z> Ll,Lr,Rl,Rr,Lu,Ru;
  Lu=Ru=std::vector<z>{0,1,0,mod-1};
  std::tie(Ll,Rl)=fuck(ch[u][0]);
  std::tie(Lr,Rr)=fuck(ch[u][1]);
  shift(Ll,Lu,1),shift(Lr,Lu,2);
  shift(Rr,Ru,1),shift(Rl,Ru,2);
  shift(Rl*Lr,ans,dep[u]);
  // printf("\e[34mfuck %d [%d]\e[0m\n",u,dep[u]),print(Lu),print(Ru),print(Rl*Lr);
  return {Lu,Ru};
}
std::pair<std::vector<z>,std::vector<z>> solve(int u){
  if(vis[u]||l[u]==r[u])return {{0,1},{0,1}};
  int siz=calcSize(u);
  int v=findSubTree(u,(siz*2)/4).first;
  if(v==-1)return fuck(u);
  std::vector<z> Lu,Ru,Lv,Rv,Lt,Rt,T;
  std::tie(Lv,Rv)=solve(v);
  vis[v]=1;
  std::tie(Lu,Ru)=solve(u);
  vis[v]=0;
  // printf("\e[31msolve %d %d (siz=%d) [%d]\e[0m\n",u,v,siz,dep[u]);
  int lmov=0,rmov=0;
  for(int p=v;p!=u;lmov+=ch[fa[p]][0]==p?1:2,rmov+=ch[fa[p]][0]==p?2:1,p=fa[p]){
    int f=fa[p],q=ch[f][0]==p?ch[f][1]:ch[f][0];
    if(ch[f][0]==p){
      T.clear(),calc(0,q,0,T),shift(T,Lt,rmov+dep[f]-dep[u]);
    }else{
      T.clear(),calc(1,q,0,T),shift(T,Rt,lmov+dep[f]-dep[u]);
    }
    // printf("-> %c %d %d %d %d %d [%d] >> ",ch[f][0]==p?'L':'R',p,q,f,lmov,rmov,(ch[f][0]==p?rmov:lmov)+dep[f]-dep[u]+1),print(T);
  }
  shift(mod-1,Lv,1);
  shift(mod-1,Rv,1);
  shift(Lv*Rt,ans,dep[u]);
  shift(Rv*Lt,ans,dep[u]);
  shift(Lv,Lu,lmov);
  shift(Rv,Ru,rmov);
  // print(Lu),print(Ru),print(Lv*Rt+Rv*Lt);
  return {Lu,Ru};
}
void solution(){
  for(int i=1;i<n;i++)read(mid[i]);
  dfsInit(_,1,n,1);
  // for(int i=1;i<=n;i++)printf("%d : %d %d : %d %d\n",i,l[i],r[i],ch[i][0],ch[i][1]);
  // fuck(1);
  solve(1);
  for(int i=1;i<(n<<1);i++)shift(1,ans,dep[i]);
  for(int i=1;i<n;i++)shift(mod-1,ans,dep[i]+2);
  for(int i=1,q;i<=m;i++){
    read(q);
    print(q<ans.size()?ans[q].x:0,'\n');
  }
}
void recycle(){
  cnt=0;
  ans.clear();
  memset(ch,0,sizeof(ch));
  memset(fa,0,sizeof(fa));
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  for(int len=1;len<(N<<1);len<<=1){
    z wn=fpow(3,(mod-1)/(len<<1)); w[len]=1;
    for(int i=1;i<len;i++)w[i+len]=w[i+len-1]*wn;
  }
  while(~scanf("%d%d",&n,&m)){
    solution();
    recycle();
  }
}
