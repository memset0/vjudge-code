#include<bits/stdc++.h>
using namespace std;
const int N=25e4+10,mod=1e9+7;
inline int sub(int x,int y){return x-y<0?x-y+mod:x-y;}
inline int add(int x,int y){return x+y>=mod?x+y-mod:x+y;}
int f[N][251],ed[N],id[N],lim[N];
int n,t;
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#else
  freopen("kebab.in","r",stdin);
  freopen("kebab.out","w",stdout);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>t;
  int m=0;
  for(int q,x,i=1;i<=n;i++){
    cin>>q>>x;
    for(int j=1;j<=q;j++)id[m+j]=i,lim[m+j]=q-x,ed[m+j]=m+q;
    m+=q;
  }
  f[0][0]=1,f[1][0]=-1;
  for(int i=0;i<=m;i++){
    for(int j=0;j<=250;j++){
      f[i+1][j]=add(f[i+1][j],f[i][j]);
    }
    if(id[i]==id[i+t+1])
      for(int j=1;j<=lim[i];j++){
        f[i+t+1][j]=add(f[i+t+1][j],f[i][j-1]);
        f[ed[i]+1][j]=sub(f[ed[i]+1][j],f[i][j-1]);
      }
    int nxt=max(i+t+1,ed[i]+1);
    if(i==0)nxt=1;
    for(int j=0;j<=lim[i];j++){
      f[nxt][1]=add(f[nxt][1],f[i][j]);
    }
  }
  int ans=0;
  for(int i=0;i<=m;i++)
    for(int j=0;j<=lim[i];j++){
      ans=add(ans,f[i][j]);
    }
  cout<<ans<<endl;
  return 0;
}