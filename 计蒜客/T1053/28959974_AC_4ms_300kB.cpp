#include<bits/stdc++.h>
using namespace std;
int main(){
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin>>n;
  vector<int> a(n);
  long long s=0;
  for(int i=0;i<n;i++){
    cin>>a[i];
    s+=a[i];
  }
  double p=s/(double)n;
  printf("%lld %.5lf\n",s,p);
}
