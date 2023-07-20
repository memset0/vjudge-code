#include<bits/stdc++.h>
using namespace std;
const int N=1e5+9;
int T,n;
unsigned int a[3][N],x; 
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif 
	ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>x;
    for(int i=0;i<3;i++)
      for(int j=1;j<=n;j++){
        cin>>a[i][j];
      }
    unsigned int y=0;
    for(int i=0;i<3;i++){
      for(int j=1;j<=n;j++){
        if((a[i][j]|x)==x){
          y|=a[i][j];
//          cerr<<i<<" "<<j<<" "<<a[i][j]<<" "<<y<<endl;
        }else{
          break;
        }
      }
    }
    if(y==x){
      cout<<"Yes"<<endl;
    }else{
      cout<<"No"<<endl;
    }
  }
}