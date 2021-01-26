#include<bits/stdc++.h>
using namespace std;
const int N=1<<12;
int n,s,len,x[N],p[N],q[N],atp[N],atq[N];
mt19937 rng(20040725^time(0));
inline int gen(int *at){static int x; do x=rng()%len; while(~at[x]); return x;}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n,len=1<<n;
  for(int i=0;i<len;i++)cin>>x[i],s^=x[i];
  if(s)return cout<<"Fou\n",0;
  memset(atp,-1,len<<2),memset(atq,-1,len<<2);
  for(int u,i=0;i<len;i++){
    for(u=i;~u;swap(u,atq[q[u]]),atp[p[u]]=-1){
//      for(int i=0;i<len;i++)cerr<<p[i]<<" \n"[i+1==len];
//      for(int i=0;i<len;i++)cerr<<atp[i]<<" \n"[i+1==len];
      p[u]=gen(atp),atp[p[u]]=u,q[u]=x[u]^p[u];
//      cerr<<u<<" "<<p[u]<<" "<<q[u]<<endl;
    }
  }
  cout<<"Shi\n";
  for(int i=0;i<len;i++)cout<<p[i]<<" \n"[i+1==len];
  for(int i=0;i<len;i++)cout<<q[i]<<" \n"[i+1==len];
  for(int i=0;i<len;i++)assert(x[i]==(p[i]^q[i]));
}