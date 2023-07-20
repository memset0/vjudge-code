#include<bits/stdc++.h>
using namespace std;
const int N=110;
int T,n,a[N];
char ans[N];
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>T;
  while(T--){
    string s;
    cin>>n>>s;
    for(int i=1;i<=n;i++){
      a[i]=s[i-1]-'0';
    }
    bool fl=true;
    for(int i=1;i<=n;i++){
      if(a[i]){
        if(fl){
          ans[i]='+';
        }else{
          ans[i]='-';
        }
        fl^=1;
      }else{
        ans[i]='+';
      }
    }
    for(int i=2;i<=n;i++){
      putchar(ans[i]);
    }
    putchar('\n');
  }
}//submit from vjudge