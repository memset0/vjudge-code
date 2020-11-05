#include<bits/stdc++.h>
using namespace std;
int main(){
  int T;
  cin>>T;
  while(T--){
    int n;
    cin>>n;
    double s=0;
    for(int i=1;i<=n;i++){
      s+=(i&1?1:-1)*(1./i);
    }
    printf("%.2lf\n",s);
  }
}