#include<bits/stdc++.h>
int main(){
  int x;
  std::vector<int> a;
  while(~scanf("%d",&x)){
    a.push_back(x);
  }
  std::sort(a.begin(),a.end());
  printf("%d\n%d\n%d\n",a[0],a[1],a[2]);
}