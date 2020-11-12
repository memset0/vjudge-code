#include<bits/stdc++.h>
template<class T> inline void read(T &x){
   x=0; register char c=getchar(); register bool f=0;
   while(!isdigit(c))f^=c=='-',c=getchar();
   while(isdigit(c))x=x*10+c-'0',c=getchar(); if(f)x=-x;
}

const int N=1e6+10;
int n,max,a[N],s[N];
long long sum,ans;

int main(){
#ifdef local
   freopen("1.in","r",stdin);
#endif
   read(n);
   for(int i=1;i<=n;i++){
      read(a[i]);
      sum+=a[i];
      s[a[i]]++;
      max=std::max(max,a[i]);
   }
   for(int i=1;i<=max;i++)s[i]+=s[i-1];
   ans=sum;
   for(int i=2;i<=max;i++){
      long long cur=0;
      for(int j=1;i*(j-1)-1<=max;j++){
         cur+=(long long)(s[std::min(i*j-1,max)]-s[i*(j-1)-1])*(j-1);
      }
      ans=std::min(ans,cur*(1-i)+sum);
      // printf("%d : %lld %lld\n",i,cur,cur*(1-i)+sum);
   }
   printf("%lld\n",ans);
}