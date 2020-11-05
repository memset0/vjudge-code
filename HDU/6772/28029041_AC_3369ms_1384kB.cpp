#include<bits/stdc++.h>
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=52;
int T,n,k;
long long ans;
struct atom{
  int a,b,c,d;
};
std::vector<atom> vet[N];
void dfs(int u,int sa,int sb,int sc,int sd){
  if(u==k){
    ans=std::max(ans,(long long)sa*sb*sc*sd);
    return;
  }
  for(const auto &it:vet[u]){
    dfs(u+1,sa+it.a,sb+it.b,sc+it.c,sd+it.d);
  }
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(T);
  while(T--){
    read(n),read(k);
    for(int i=0;i<k;i++)vet[i].clear();
    for(int t,a,b,c,d,i=0;i<n;i++){
      read(t),read(a),read(b),read(c),read(d),--t;
      vet[t].push_back({a,b,c,d});
    }
    for(int i=0;i<k;i++)if(!vet[i].size()){
      vet[i].push_back({0,0,0,0});
    }
    std::sort(vet,vet+k,[](const std::vector<atom> &a,const std::vector<atom> &b){
      return a.size()<b.size();
    });
    ans=0;
    dfs(0,100,100,100,100);
    printf("%lld\n",ans);
  }
  // fprintf(stderr,"clocks: %.4lf\n",clock()/(double)CLOCKS_PER_SEC);
}