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
    sort(a+1,a+m+1);
    reverse(a+1,a+m+1);
    bool ans=true;
    int x=n/k;
    int y=n%k;
    for(int i=1;i<=m;i++){
      if(a[i]<=x){
        break;
      }else if(a[i]==x+1&&y){
        y-=1;
      }else{
        ans=false;
        break;
      }
    }
    if(ans){
      puts("yes");
    }else{
      puts("no");
    }
  }
}
/*
1
27480 9 4
11511 5829 3159 2717 1557 1050 695 522 440
*/