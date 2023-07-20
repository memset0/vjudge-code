#include<bits/stdc++.h>
using namespace std;
const int N=110;
int T,n,mx,a[N],cnt[N];
int main(){
  cin.tie(0),ios::sync_with_stdio(0);
  cin>>T;
  while(T--){
    memset(cnt,0,sizeof(cnt));
    cin>>n;
    for(int i=1;i<=n;i++){
      cin>>a[i];
      ++cnt[a[i]];
      mx=max(mx,a[i]);
    }
//    for(int i=0;i<=mx;i++)cout<<cnt[i]<<" \n"[i==mx];
    bool fl=true;
    for(int i=1;i<=mx;i++){
      if(cnt[i-1]<cnt[i]){
        fl=false;
        break;
      }
    }
    cout<<(fl?"YES":"NO")<<endl;
  }
}