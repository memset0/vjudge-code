#include<bits/stdc++.h>
using namespace std;
const int N=3e3+9;
int n,x,y,z,lim=N-4,a[N][N],b[N][N];
string op;
long long ans;
int main(){
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>op>>x>>y>>z;
    if(op=="A"){
      x+=lim/2-z/2;
      y+=lim/2-z/2;
      a[x][y]=max(a[x][y],z);
    }else{
      x+=lim/2-z/2;
      y+=lim/2;
      b[x][y]=max(b[x][y],z);
    }
  }
  for(int i=1;i<=lim;i++)
    for(int j=1;j<=lim;j++){
      a[i][j]=max({a[i][j],a[i-1][j-1]-1,a[i-1][j]-1,a[i][j-1]-1});
      b[i][j]=max({b[i][j],b[i-1][j]-1,b[i-1][j-1]-2,b[i-1][j+1]-2});
    }
  for(int i=1;i<=lim;i++)
    for(int j=1;j<=lim;j++)
      if(a[i][j])ans+=4;
      else{
        if(b[i][j])ans++;
        if(b[i][j+1])ans++;
        if(b[i][j]>1||b[i][j+1]>1)ans++;
        if(b[i-1][j]>1||b[i-1][j+1]>1)ans++;
      }
  printf("%lld",ans>>2);
  switch(ans&3){
    case 0:printf(".00\n");break;
    case 1:printf(".25\n");break;
    case 2:printf(".50\n");break;
    case 3:printf(".75\n");break;
  }
}