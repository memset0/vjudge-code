#include<iostream>
using namespace std;
int main(){
  int n;
  vector<int> a,b;
  while(cin>>n){
    a.resize(n),b.resize(n);
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)cin>>b[i];
    a.insert(a.end(),b.begin(),b.end());
    sort(a.begin(),a.end());
    cout<<a[n]<<endl;
  }
}