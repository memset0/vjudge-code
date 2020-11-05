#include<bits/stdc++.h>
int main(){
  std::vector<int> a(10);
  for(int i=0;i<=9;i++){
    scanf("%d",&a[i]);
  }
  std::sort(a.begin(),a.end(),std::greater<int>());
  printf("%d\n%d\n%d\n",a[0],a[1],a[2]);
}