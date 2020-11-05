#include<bits/stdc++.h>
#define val_t uint64_t
template<class T> inline void read(T &x){
  x=0; char c=getchar(); bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
template<class T> T gcd(T n,T m){return m?gcd(m,n%m):n;}
const int N=1e5+10,M=sqrt(N)+10;
int n,pcnt,vis[N],pri[N];
val_t sum,tmp[N],mu[N],t[4][N],a[6][N],b[6][N],res[N];
std::vector<int> vet[M];
void cpy(val_t *src,val_t *dst,int n){
  memcpy(dst,src,(n+1)<<3);
}
void plusup(val_t *src,val_t *dst,int n){
  memset(dst,0,(n+1)<<3);
  for(int i=1;i<=n;i++)for(int j=1,k=i;k<=n;j++,k+=i)dst[i]+=src[k];
}
void plusdown(val_t *src,val_t *dst,int n){
  memset(dst,0,(n+1)<<3);
  for(int i=1;i<=n;i++)for(int j=1,k=i;k<=n;j++,k+=i)dst[k]+=src[i];
}
void dirichlet(val_t *f,val_t *g,val_t *dst,int n){
  memset(dst,0,(n+1)<<3);
  for(int i=1;i<=n;i++)for(int j=1,k=i;k<=n;j++,k+=i)dst[k]+=f[i]*g[j];
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(n);
  for(int i=0;i<6;i++)for(int j=1;j<=n;j++)read(a[i][j]);
  mu[1]=1;
  for(int i=2;i<=n;i++){
    if(!vis[i])pri[++pcnt]=i,mu[i]=-1;
    for(int j=1;j<=pcnt&&i*pri[j]<=n;j++){
      vis[i*pri[j]]=1; if(i%pri[j]==0)break; mu[i*pri[j]]=-mu[i];
    }
  }
  cpy(a[2],tmp,n),plusup(tmp,a[2],n);
  cpy(a[4],tmp,n),dirichlet(tmp,mu,a[4],n);
  cpy(a[5],tmp,n),dirichlet(tmp,mu,a[5],n);
  int sqr=sqrt(n);
  for(int i=1;i<=sqr;i++)for(int j=1;i*j<=n;j++)if(gcd(i,j)==1){
    vet[i].push_back(j);
  }
  int cnt=0;
  for(int d=1;d<=n;d++){
    int m=n/d,sqr=sqrt(m);
    for(int i=0;i<6;i++)for(int j=1,k=d;j<=m;j++,k+=d)b[i][j]=a[i][k];
    cpy(b[3],tmp,m),dirichlet(tmp,mu,b[3],m);
    val_t *c[4]={b[0],b[1],b[4],b[5]};
    for(int p=1;p<=sqr;p++){
      int lim=m/p;
      while(vet[p].size()&&vet[p].back()>lim)vet[p].pop_back();
      if(vet[p].empty())break;
      for(int _=0;_<2;_++){
        memset(t[0],0,(m+1)<<3),memset(t[1],0,(m+1)<<3);
        for(int i=p;i<=m;i+=p)t[0][i]=c[0][i];
        for(int i=1;i<=m;i++)for(int j=1,k=i;k<=m;j++,k+=i)t[1][i]+=b[3][i]*t[0][k];
        plusdown(t[1],t[2],m);
        for(int i=1;i<=m;i++)t[2][i]*=c[1][i];
        plusup(t[2],t[3],m);
        for(int q:vet[p]){
          if(_&&q<=sqr)continue;
          sum+=c[2][p]*c[3][q]*b[2][p*q]*t[3][q];
          ++cnt;
        }
        std::swap(c[0],c[1]),std::swap(c[2],c[3]);
      }
    }
    // fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
  }
  printf("%llu\n",sum);
  fprintf(stderr,"%d\n",cnt);
  fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}