#include<bits/stdc++.h>
template<class T> inline void read(T &x){
  x=0; register char c=getchar(); register bool f=0;
  while(!isdigit(c))f^=c=='-',c=getchar();
  while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}
const int N=3e5+10;
int T,n,cnt;
long long ans[N];
std::multiset<int> set;
std::vector<std::pair<int,int>> a;
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  read(T);
  while(T--){
    read(n);
    for(int i=1,a,b;i<=n;i++){
      read(a),read(b);
      ::a.push_back(std::make_pair(a,b));
    }
    std::sort(a.begin(),a.end());
    long long now=0;
    auto spend=[&](long long lst){
      // printf("spend %lld\n",lst);
      while(lst&&set.size()){
        if(lst<*set.begin()){
          int tmp=*set.begin()-lst;
          now+=lst;
          lst=0;
          set.erase(set.begin());
          set.insert(tmp);
        }else{
          now+=*set.begin();
          lst-=*set.begin();
          ans[++cnt]=now;
          // printf("end[%d] %lld\n",cnt,now);
          set.erase(set.begin());
          // for(int x:set)printf("%d ",x);putchar('\n');
        }
      }
      now+=lst;
    };
    for(int i=0,j;i<a.size();i=j+1){
      spend(a[i].first-(i?a[i-1].first:0));
      for(j=i;j+1<a.size()&&a[j+1].first==a[i].first;j++);
      for(int k=i;k<=j;k++)set.insert(a[k].second);
    }
    spend(1145141919810000);
    for(int i=1;i<=n;i++)printf("%lld%c",ans[i]," \n"[i==n]);
    cnt=0,a.clear(),set.clear();
  }
}