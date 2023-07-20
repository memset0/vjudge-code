#include<bits/stdc++.h>
using namespace std;
long long T,n,k,g,l,r,mid,ans;
int main(){
  cin.tie(0),ios::sync_with_stdio(0);
  cin>>T;
  while(T--){
    cin>>n>>k>>g;
    ans=min(k,((g-1)>>1)*n/g);
    cout<<(long long)(ans)*g<<endl;
  }
}