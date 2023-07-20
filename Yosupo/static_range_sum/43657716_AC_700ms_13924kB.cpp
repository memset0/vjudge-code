#include<bits/stdc++.h>
using namespace std;
const int N=5e5+9;
int n,q,l,r,a[N];
long long s[N];
int main(){
  cin>>n>>q;
  for(int i=1;i<=n;i++){
    cin>>a[i];
    s[i]=s[i-1]+a[i];
  }
  while(q--){
    cin>>l>>r;
    cout<<(s[r]-s[l])<<endl;
  }
}