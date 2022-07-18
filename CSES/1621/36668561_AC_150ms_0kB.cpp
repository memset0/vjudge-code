#include<bits/stdc++.h>
using namespace std;
int n,x;
set<int> p;
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++){
    cin>>x;
    p.insert(x);
  }
  cout<<p.size()<<endl;
}