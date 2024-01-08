#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int x[N],y[N],pre[N],n,cnt[2][2][2];
long long ans=0;
int main(){
  cin>>n;
  for(int i=1;i<=n;i++){
    scanf("%d%d",&x[i],&y[i]);
    x[i]=x[i]&1;
    y[i]=y[i]&1;
  }
  x[n+1]=x[1],y[n+1]=y[1];
  for(int i=2;i<=n+1;i++){
    pre[i]=pre[i-1]^(x[i-1]&y[i])^(y[i-1]&x[i]);
  }
  if(pre[n+1]){
    puts("0");
    return 0;
  }
  for(int r=1;r<=n;r++){
    for(int i=0;i<2;i++)
      for(int j=0;j<2;j++)
        for(int k=0;k<2;k++)
          if(!(pre[r]^i^(j&y[r])^(k&x[r]))){
            ans+=cnt[i][j][k];
          }
    ++cnt[pre[r]][x[r]][y[r]];
  }
  cout<<ans-n<<endl;
}//dafdsfsadfads