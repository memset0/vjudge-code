#include<bits/stdc++.h>
using namespace std;
const int f[]={1,10,100,1000,10000,100000,1000000,10000000};
int T,a,b,c;
long long k;
int main(){
#ifdef memset0
  freopen("1.in","r",stdin);
#endif
  cin.tie(0),ios::sync_with_stdio(0);
  cin>>T;
  while(T--){
    cin>>a>>b>>c>>k;
    bool fl=false;
    for(int x=f[a-1];x<f[a];x++){
      int yl=max(f[b-1],f[c-1]-x);
      int yr=min(f[c]-1-x,f[b]-1);
//      cerr<<x<<" "<<yl<<" "<<yr<<endl;
      if(yl<=yr){
        if(k<=(yr-yl+1)){
          int y=yl+k-1;
          int z=x+y;
          fl=true;
          cout<<x<<" + "<<y<<" = "<<z<<endl;
          break;
        }else{
          k-=yr-yl+1;
        }
      }
    }
    if(!fl){
      cout<<-1<<endl;
    }
//    break;
  }
}