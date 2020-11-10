#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int INF=0x3f3f3f3f;
LL mod;
const int N=100005;

int sz=3;
struct Mat{
  LL a[3][3];
  Mat(){
    memset(a,0,sizeof a);
  }
  Mat operator*(const Mat &rhs) const{
    Mat res;
    for(int i=0;i<sz;i++){
      for(int j=0;j<sz;j++){
        for(int k=0;k<sz;k++){
          res.a[i][j]+=a[i][k]*rhs.a[k][j];
          res.a[i][j]%=mod;
        }
      }
    }
    return res;
  }
  Mat operator^(LL n) const{
    Mat res,x=*this;
    for(int i=0;i<sz;i++) res.a[i][i]=1;
    while(n){
      if(n&1) res=res*x;
      x=x*x;
      n>>=1;
    }
    return res;
  }
};

int main(){
  int n;
  cin>>n>>mod;
  Mat A;
  A.a[0][0]=A.a[0][1]=A.a[1][0]=A.a[2][0]=A.a[2][2]=1;
  A=A^n-1;
  cout<<(A.a[2][0]+A.a[2][1]+A.a[2][2])%mod<<endl;
  return 0;
}
