#include<bits/stdc++.h>
using namespace std;
int t,a,b;
string opt;
int main(){
  cin>>t;
  while(t--){
    cin>>a>>opt>>b;
    if(opt=="add"){
      cout<<a+b<<endl;
    }else if(opt=="sub"){
      cout<<a-b<<endl;
    }else if(opt=="mul"){
      cout<<(long long)a*b<<endl;
    }else if(opt=="div"){
      cout<<a/b<<endl;
    }else if(opt=="mod"){
      cout<<a%b<<endl;
    }
  }
}