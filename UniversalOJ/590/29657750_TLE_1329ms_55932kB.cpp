#include<bits/stdc++.h>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
const int N=1e6+9;
int n,m,ans;
struct Atom{
  int l,r;
  inline bool operator<(const Atom &rhs)const{return l<rhs.l;}
}a[N];
__gnu_pbds::priority_queue<int,less<int>,__gnu_pbds::pairing_heap_tag> q;
int main(){
#ifdef memset0
  freopen("a2.in","r",stdin);
#endif
  cin>>n>>m;
  for(int i=1;i<=n;i++)cin>>a[i].l>>a[i].r;
  sort(a+1,a+n+1);
  for(int k=1,t=0;k<=n||q.size();){
    while(a[k].l==t)q.push(-a[k++].r);
    for(int c=min<int>(q.size(),m);c--;)ans=max(ans,t+q.top()),q.pop();
    t=q.size()?t+1:a[k].l;
  }
  cout<<ans<<endl;
}
