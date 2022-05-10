#include<bits/stdc++.h>
using namespace std;
const int N=1e3+9;
int n,x[N],ans[64][64];
long long a[N];
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++)cin>>a[i],x[i]=63-__builtin_clzll(a[i]);
  for(int i=0;i<64;i++)
    for(int j=i+1;j<64;j++){
      for(int k=0;k<3;k++){
        int x=(i>>(k<<1))&3;
        int y=(j>>(k<<1))&3;
        if(x<y){
          ans[i][j]=k+1;
          break;
        }
      }
    }
  // for(int i=1;i<64;i++){
  //   for(int j=0;j<i;j++)cout<<ans[j][i]<<" ";
  //   cout<<endl;
  // }
  for(int i=2;i<=n;i++){
    for(int j=1;j<i;j++)if(x[i]!=x[j])cout<<ans[x[j]][x[i]]<<" "; else cout<<"1 ";
    cout<<'\n';
  }
}