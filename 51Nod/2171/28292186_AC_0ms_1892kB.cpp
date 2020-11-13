#include<bits/stdc++.h>
using namespace std;
int T,n;
inline long long calc(int m){
  return (long long)m*(m+1)/2;
}
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>T;
  while(T--){
    cin>>n,--n;
    cout<<calc(n/3)*3+calc(n/5)*5-calc(n/15)*15<<endl;
  }
}