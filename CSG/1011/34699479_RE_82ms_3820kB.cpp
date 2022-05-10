#include<bits/stdc++.h>
using namespace std;
int main(){
  int n;
  vector<int> a;
  while(~scanf("%d",&n)){
    a.resize(n*2);
    for(int i=0;i<n*2;i++)scanf("%d",&a[i]);
    sort(a.begin(),a.end());
    cout<<a[n-1]<<endl;
  }
}