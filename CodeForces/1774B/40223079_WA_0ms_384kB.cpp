#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int T,n,m,k,a[N];
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>m>>k,a[0]=a[m+1]=0;
    int max=0;
    for(int i=1;i<=m;i++){
      cin>>a[i];
      if(a[i]>max){
        max=a[i];
      }
    }
    if(max<=(n+k-2)/(k-1)){
      cout<<"YES"<<endl;
    }else{
      cout<<"NO"<<endl;
    }
  }
}
/*
1
27480 9 4
11511 5829 3159 2717 1557 1050 695 522 440
*/