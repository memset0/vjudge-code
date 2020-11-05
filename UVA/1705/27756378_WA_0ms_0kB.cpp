#include<bits/stdc++.h>
using namespace std;
const int N=110;
int n,d,x[N],y[N],p[N];
bitset<N> s,ans,a[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>d;
  for(int i=1;i<=n;i++)cin>>x[i]>>y[i];
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<=d*d)
        a[i][j]=1;
  for(int i=1;i<=n;i++)p[i]=i;
  for(int T=n*n;T;T--){
    random_shuffle(p+1,p+n+1);
    s.reset();
    for(int i=1;i<=n;i++)if((a[p[i]]&s)==s)s.set(p[i]);
    if(s.count()>ans.count())ans=s;
  }
  cout<<ans.count()<<endl;
  for(int i=1;i<=n;i++)if(ans[i])cout<<i<<" ";
}