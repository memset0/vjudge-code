#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m,w,p[N],q[N];
struct atom{
  int p,h,i;
  bool operator<(const atom &e) const{return h^e.h?h<e.h:i<e.i;}
}a[N],b[N];
set<atom> s,t;
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i].p,a[i].i=i;
  for(int i=1;i<=n;i++)cin>>a[i].h,a[i].h<<=1;
  for(int i=1;i<=n;i++)cin>>b[i].p,b[i].i=i;
  for(int i=1;i<=n;i++)cin>>b[i].h,b[i].h<<=1;
  sort(a+1,a+n+1,[](const atom &a,const atom &b){return a.p<b.p;});
  sort(b+1,b+n+1,[](const atom &a,const atom &b){return a.p<b.p;});
  for(int j=1,k=1;j<=n||k<=n;){
    if(j<=k){
      for(w=a[j].p;a[j].p==w;j++)s.insert(a[j]);
    }else{
      for(w=b[k].p;b[k].p==w;k++)t.insert(b[k]);
    }
    if(s.size()>t.size()){
      for(atom v:t){
        v.h++;
        auto it=s.upper_bound(v);
        if(it==s.end())puts("impossible"),exit(0);
        p[++m]=it->i,q[m]=v.i;
        s.erase(it);
      }
      t.clear();
    }else{
      for(atom v:s){
        v.h--;
        auto it=t.lower_bound(v);
        if(it==t.begin())puts("impossible"),exit(0);
        q[++m]=(--it)->i,p[m]=v.i;
        t.erase(it);
      }
      s.clear();
    }
  }
  for(int i=1;i<=n;i++)cout<<p[i]<<" \n"[i==n];
  for(int i=1;i<=n;i++)cout<<q[i]<<" \n"[i==n];
}
