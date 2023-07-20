#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  int q,op,k,v;
  map<int,int> a;
  cin>>q;
  while(q--){
    cin>>op;
    if(op){
      cin>>k;
      auto it=a.find(k);
      cout<<(it==a.end()?0:it->second)<<endl;
    }else{
      cin>>k>>v;
      a[k]=v;
    }
  }
}