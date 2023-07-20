#include<bits/stdc++.h>
using namespace std;
const int N=5e3+9;
int n,m,l,r,q[N][2],c[N],s[N][N];
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>m;
  for(int i=0;i<m;i++){
    cin>>q[i][0]>>q[i][1];
    n=max(n,q[i][1]); 
  }
  for(int i=1;i<=n;i++)
    for(int j=i;j<=n;j+=i){
      c[j]+=1;
    }
  for(int l=1;l<=n;l++){
    s[l][l]=l;
    for(int r=l+1;r<=n;r++){
      s[l][r]=c[r]>c[s[l][r-1]]?r:s[l][r-1];
    }
  }
  for(int i=0;i<m;i++){
    cout<<s[q[i][0]][q[i][1]]<<endl;
  }
}