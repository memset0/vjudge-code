#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin>>n;
  vector<int> a(n);
  for(int i=0;i<n;i++){
    cin>>a[i];
  }
  reverse(a.begin(),a.end());
  for(int i=0;i<n;i++){
    cout<<a[i]<<" \n"[i+1==n];
  }
}
