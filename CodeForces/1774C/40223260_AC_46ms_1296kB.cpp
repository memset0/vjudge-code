#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int T,n,a[N];
string s;
int main(){
  ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
  cin>>T;
  while(T--){
    cin>>n>>s,a[n]=0;
    for(int i=1;i<n;i++){
      a[i]=s[i-1]-'0';
    }
    int lst[2]={-1,-1};
    for(int i=1;i<n;i++){
      lst[a[i]]=i;
      if(a[i]){
        swap(lst[0],lst[1]);
      }
      if(lst[1]==-1){
        cout<<1<<" ";
      }else{
        int x=i-lst[1];
        cout<<i+1-x<<" ";
      }
      if(a[i]){
        swap(lst[0],lst[1]);
      }
    }
    cout<<endl;
  }
}