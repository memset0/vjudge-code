#include<bits/stdc++.h>
using namespace std;
int n,m,x;
map<int,int> p;
int main(){
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>n;
  for(int i=1;i<=n;i++)cin>>x,p[x]++;
  cin>>m;
  for(int i=1;i<=m;i++)cin>>x,p[x]--;
  for(const auto &it:p)
    if(it.second<0){
      puts("NO");
      return 0;
    }
  puts("YES");
}