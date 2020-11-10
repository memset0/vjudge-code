#include<bits/stdc++.h>
#define popc __builtin_popcount
using namespace std;
const int N=22;
int n,m,t,av[N],bv[N],a[N][N],b[N][N];
bool pos[1<<20];
vector<int> f,g;
long long ans;
string s;
void solve(int n,int m,int a[N][N],int v[N],vector<int> &f){
  static int c[N];
  for(int i=0;i<n;i++){
    c[i]=0;
    for(int j=0;j<m;j++)c[i]|=a[i+1][j+1]<<j;
  }
  for(int x=0;x<(1<<n);x++){
    int s=0;
    for(int i=0;i<n;i++)if((x>>i)&1)s|=c[i];
    pos[x]=popc(x)<=popc(s);
    for(int i=0;i<n;i++)if((x>>i)&1)pos[x]&=pos[x^(1<<i)];
    if(pos[x]){
      int w=0;
      for(int i=0;i<n;i++)if((x>>i)&1)w+=v[i+1];
      f.push_back(w);
    }
  }
  sort(f.begin(),f.end());
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n>>m;
  for(int i=1;i<=n;i++){
    cin>>s;
    for(int j=1;j<=m;j++)a[i][j]=b[j][i]=s[j-1]=='1';
  }
  for(int i=1;i<=n;i++)cin>>av[i];
  for(int i=1;i<=m;i++)cin>>bv[i];
  cin>>t;
  solve(n,m,a,av,f);
  solve(m,n,b,bv,g);
  for(int i=0,j=(int)g.size()-1;i<f.size();i++){
    while(j>0&&f[i]+g[j-1]>=t)j--;
    if(f[i]+g[j]>=t){
      // printf("%d %d -> %d\n",i,j,(int)g.size()-j);
      ans+=(int)g.size()-j;
    }
  }
  cout<<ans<<endl;
}