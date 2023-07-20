#include<bits/stdc++.h>
using namespace std;
const int N=109;
int T,n,a[N];
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    cin>>n;
    int s=0,c=0;
    for(int i=1;i<=n;i++){
      cin>>a[i];
      s+=a[i];
      if(a[i]==-1)c++;
    }
    int x=s<0?((-s+1)>>1):0;
    if((c&1)^(x&1))++x;
    cout<<x<<endl;
  }
} 