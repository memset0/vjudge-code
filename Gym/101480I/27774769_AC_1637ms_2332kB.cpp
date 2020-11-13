#include<bits/stdc++.h>
using namespace std;
const int N=510;
int n,q,A,B,C;
bool vis[N][N];
double tmp,r[N][N];
inline double calc(int x,int y){return abs((A*x+B*y+C)/tmp);}
void solve(){
  int x1,y1,x2,y2,ans=0;
  cin>>x1>>y1>>x2>>y2;
  A=y2-y1,B=x1-x2,C=-A*x1-B*y1;
  tmp=sqrt(A*A+B*B);
  if(x1>x2)swap(x1,x2);
  if(y1>y2)swap(y1,y2);
  if(x1==x2)for(int j=y1;j<=y2;++j)ans+=vis[x1][j];
  else{
    for(int i=x1;i<=x2;++i){
      int L=(int)((double)(-C-A*(max(x1,i-1)))/(double)B),R=(int)((double)(-C-A*(min(x2,i+1)))/(double)B);
      if(L>R)swap(L,R);
      L=max(y1,L-1),R=min(y2,R+1);
      for(int j=L;j<=R;++j)if(vis[i][j])ans+=r[i][j]>=calc(i,j);
    }
  }
  printf("%d\n",ans);
}
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(int x,y,i=1;i<=n;++i){
    cin>>x>>y>>r[x][y];
    vis[x][y]=true;
  }
  cin>>q;
  while(q-->0)solve();
}