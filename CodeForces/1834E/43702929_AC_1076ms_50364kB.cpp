#include<bits/stdc++.h>
using namespace std;
const int N=3e5+9,L=20,M=3e6;
int T,n,a[N],st[N][L];
vector<int> ans;
int lcm(int x,int y){
  if(x==-1||y==-1)return -1;
  long long r=(long long)x/__gcd(x,y)*y;
  if(r>M){
    return -1;
  }else{
    return r;
  }
}
int main(){
#ifdef memset0
  freopen("E.in","r",stdin);
#endif
  ios::sync_with_stdio(0),cin.tie(0);
  cin>>T;
  while(T--){
    ans.clear();
    cin>>n;
    for(int i=1;i<=n;i++){
      cin>>a[i];
      st[i][0]=a[i];
    }
    for(int i=1;i<L;i++)
      for(int j=1;j<=n;j++){
        if((j+(1<<i)-1)>n){
          st[j][i]=-1;
        }else{
          st[j][i]=lcm(st[j][i-1],st[j+(1<<i-1)][i-1]);
        }
      }
    for(int l=1;l<=n;l++){
      int r=l;
      int cur=a[l];
      ans.push_back(cur);
      while(r<=n){
        for(int i=L-1;i>=0&&r<=n;i--)
          if(st[r][i]!=-1&&cur%st[r][i]==0){
            r+=1<<i;
          }
        if(r>n){
          break;
        }
//        cerr<<"<<<"<<l<<" "<<r<<" "<<cur<<endl;
        cur=lcm(cur,a[r]);
        if(cur==-1){
          break;
        }
        ans.push_back(cur);
      }
    }
    sort(ans.begin(),ans.end());
    unique(ans.begin(),ans.end());
    int mex=-1;
    for(int i=0;i<ans.size();i++){
      if(ans[i]!=(i+1)){
        mex=i+1;
        break;
      }
    }
    if(mex==-1){
      mex=ans.size()+1;
    }
    cout<<mex<<endl;
  }
}